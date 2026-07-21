// Algoritmo Bubble Sort para ordenação de vetor
function bubbleSort(arr) {
  const n = arr.length;
  for (let i = 0; i < n - 1; i++) {
    for (let j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        const temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  return arr;
}

class BTreeNode {
  // Cria nó da B-Tree com grau mínimo e indicação de folha
  constructor(t, leaf = false) {
    this.t = t;
    this.leaf = leaf;
    this.keys = [];
    this.children = [];
  }

  // Verifica se o nó tem o número máximo de chaves
  isFull() {
    return this.keys.length === 2 * this.t - 1;
  }

  // Busca chave no nó ou desce ao filho apropriado
  search(key) {
    let idx = 0;
    while (idx < this.keys.length && key > this.keys[idx]) {
      idx++;
    }
    if (idx < this.keys.length && this.keys[idx] === key) {
      return this;
    }
    if (this.leaf) {
      return null;
    }
    return this.children[idx].search(key);
  }

  // Percorre em ordem e agrega chaves no array resultado
  traverse(result = []) {
    for (let i = 0; i < this.keys.length; i++) {
      if (!this.leaf) {
        this.children[i].traverse(result);
      }
      result.push(this.keys[i]);
    }
    if (!this.leaf) {
      this.children[this.keys.length].traverse(result);
    }
    return result;
  }
}

class BTree {
  // Cria árvore B-Tree com grau mínimo
  constructor(t = 2) {
    this.t = t;
    this.root = new BTreeNode(t, true);
  }

  // Busca chave a partir da raiz
  search(key) {
    if (!this.root) {
      return null;
    }
    return this.root.search(key);
  }

  // Insere chave na árvore, dividindo raiz se necessário
  insert(key) {
    if (this.search(key)) {
      return false;
    }

    const r = this.root;
    if (r.isFull()) {
      const s = new BTreeNode(this.t, false);
      s.children[0] = r;
      this.splitChild(s, 0);
      this.root = s;
      this.insertNonFull(s, key);
    } else {
      this.insertNonFull(r, key);
    }
    return true;
  }

  // Insere chave em nó não cheio
  insertNonFull(node, key) {
    let i = node.keys.length - 1;
    if (node.leaf) {
      while (i >= 0 && key < node.keys[i]) {
        i--;
      }
      node.keys.splice(i + 1, 0, key);
      bubbleSort(node.keys);
    } else {
      while (i >= 0 && key < node.keys[i]) {
        i--;
      }
      i += 1;
      if (node.children[i].isFull()) {
        this.splitChild(node, i);
        if (key > node.keys[i]) {
          i += 1;
        }
      }
      this.insertNonFull(node.children[i], key);
    }
  }

  // Divide filho cheio ao inserir
  splitChild(parent, index) {
    const t = this.t;
    const child = parent.children[index];
    const sibling = new BTreeNode(t, child.leaf);

    sibling.keys = child.keys.splice(t);
    const middleKey = child.keys.pop();

    if (!child.leaf) {
      sibling.children = child.children.splice(t);
    }

    parent.children.splice(index + 1, 0, sibling);
    parent.keys.splice(index, 0, middleKey);
  }

  // Remove chave da árvore e ajusta raiz se necessário
  delete(key) {
    if (!this.root) {
      return false;
    }
    const removed = this.deleteFromNode(this.root, key);
    if (this.root.keys.length === 0 && !this.root.leaf) {
      this.root = this.root.children[0];
    }
    if (this.root.keys.length === 0 && this.root.leaf) {
      this.root = new BTreeNode(this.t, true);
    }
    return removed;
  }

  // Remove chave do nó ou delega a remoção para filhos
  deleteFromNode(node, key) {
    const idx = this.findKey(node, key);

    if (idx < node.keys.length && node.keys[idx] === key) {
      if (node.leaf) {
        node.keys.splice(idx, 1);
        return true;
      }
      return this.deleteInternal(node, key, idx);
    }

    if (node.leaf) {
      return false;
    }

    let flag = idx === node.keys.length;
    if (node.children[idx].keys.length < this.t) {
      this.fill(node, idx);
    }

    if (flag && idx > node.keys.length) {
      return this.deleteFromNode(node.children[idx - 1], key);
    }
    return this.deleteFromNode(node.children[idx], key);
  }

  // Remove chave interna usando predecessor, sucessor ou mesclagem
  deleteInternal(node, key, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    if (child.keys.length >= this.t) {
      const pred = this.getPredecessor(child);
      node.keys[idx] = pred;
      return this.deleteFromNode(child, pred);
    }

    if (sibling.keys.length >= this.t) {
      const succ = this.getSuccessor(sibling);
      node.keys[idx] = succ;
      return this.deleteFromNode(sibling, succ);
    }

    this.merge(node, idx);
    return this.deleteFromNode(child, key);
  }

  // Retorna índice da primeira chave maior ou igual ao valor
  findKey(node, key) {
    let idx = 0;
    while (idx < node.keys.length && node.keys[idx] < key) {
      idx += 1;
    }
    return idx;
  }findKey(node, key) {
    let idx = 0;
    while (idx < node.keys.length && node.keys[idx] < key) {
      idx += 1;
    }
    return idx;
  }

  // Retorna predecessor do nó
  getPredecessor(node) {
    let current = node;
    while (!current.leaf) {
      current = current.children[current.keys.length];
    }
    return current.keys[current.keys.length - 1];
  }

  // Retorna sucessor do nó
  getSuccessor(node) {
    let current = node;
    while (!current.leaf) {
      current = current.children[0];
    }
    return current.keys[0];
  }

  // Preenche nó filho com menos chaves que o mínimo
  fill(node, idx) {
    if (idx !== 0 && node.children[idx - 1].keys.length >= this.t) {
      this.borrowFromPrev(node, idx);
    } else if (idx !== node.keys.length && node.children[idx + 1].keys.length >= this.t) {
      this.borrowFromNext(node, idx);
    } else {
      if (idx !== node.keys.length) {
        this.merge(node, idx);
      } else {
        this.merge(node, idx - 1);
      }
    }
  }

  // Empresta chave do irmão anterior
  borrowFromPrev(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx - 1];

    child.keys.unshift(node.keys[idx - 1]);
    if (!child.leaf) {
      child.children.unshift(sibling.children.pop());
    }

    node.keys[idx - 1] = sibling.keys.pop();
  }

  // Empresta chave do irmão posterior
  borrowFromNext(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    child.keys.push(node.keys[idx]);
    if (!child.leaf) {
      child.children.push(sibling.children.shift());
    }

    node.keys[idx] = sibling.keys.shift();
  }

  // Mescla filho com o irmão direito
  merge(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    child.keys.push(node.keys[idx], ...sibling.keys);
    if (!child.leaf) {
      child.children.push(...sibling.children);
    }

    node.keys.splice(idx, 1);
    node.children.splice(idx + 1, 1);
  }

  // Retorna chaves em ordem crescente
  inorder() {
    return this.root.traverse([]);
  }

  // Limpa a árvore, restaurando raiz vazia
  clear() {
    this.root = new BTreeNode(this.t, true);
  }
}

const tree = new BTree(2);
const keyInput = document.getElementById('keyInput');
const treeRoot = document.getElementById('treeRoot');
const status = document.getElementById('status');

// Atualiza elemento de status com mensagem
function setStatus(message) {
  status.textContent = message;
}

// Cria representação visual recursiva do nó
function renderTree(node) {
  if (!node) {
    return null;
  }

  const wrapper = document.createElement('div');
  wrapper.className = 'tree-node-group';

  const nodeBox = document.createElement('div');
  nodeBox.className = 'node';
  nodeBox.textContent = node.keys.join(' | ');
  wrapper.appendChild(nodeBox);

  if (!node.leaf) {
    const children = document.createElement('div');
    children.className = 'children';

    node.children.forEach((child) => {
      children.appendChild(renderTree(child));
    });

    wrapper.appendChild(children);
  }

  return wrapper;
}

// Renderiza a árvore na interface
function render() {
  treeRoot.innerHTML = '';
  if (!tree.root || tree.root.keys.length === 0) {
    const empty = document.createElement('p');
    empty.className = 'empty';
    empty.textContent = 'Árvore vazia. Insira um valor para começar.';
    treeRoot.appendChild(empty);
    return;
  }
  treeRoot.appendChild(renderTree(tree.root));
}

// Lê valor do input e insere na árvore
function insertValue() {
  const value = Number(keyInput.value);
  if (!Number.isInteger(value)) {
    setStatus('Digite um número inteiro válido.');
    return;
  }

  const inserted = tree.insert(value);
  render();
  setStatus(inserted
    ? `Valor ${value} inserido. Ordem: ${tree.inorder().join(' -> ')}`
    : `Valor ${value} já existe na árvore.`);
  keyInput.value = '';
}

// Lê valor do input e remove da árvore
function deleteValue() {
  const value = Number(keyInput.value);
  if (!Number.isInteger(value)) {
    setStatus('Digite um número inteiro válido.');
    return;
  }

  const removed = tree.delete(value);
  render();
  setStatus(removed ? `Valor ${value} removido.` : `Valor ${value} não encontrado.`);
  keyInput.value = '';
}

// Lê valor do input e busca na árvore
function searchValue() {
  const value = Number(keyInput.value);
  if (!Number.isInteger(value)) {
    setStatus('Digite um número inteiro válido.');
    return;
  }

  const found = tree.search(value);
  setStatus(found ? `Valor ${value} encontrado.` : `Valor ${value} não encontrado.`);
}

// Popula árvore com exemplo de valores
function populateExample() {
  tree.clear();
  [10, 20, 5, 6, 12, 30, 7, 17].forEach((value) => tree.insert(value));
  render();
  setStatus(`Exemplo carregado. Ordem: ${tree.inorder().join(' -> ')}`);
}

// Limpa a árvore e atualiza interface
function clearTree() {
  tree.clear();
  render();
  setStatus('Árvore limpa.');
}

window.addEventListener('DOMContentLoaded', () => {
  render();
  document.getElementById('insertBtn').addEventListener('click', insertValue);
  document.getElementById('deleteBtn').addEventListener('click', deleteValue);
  document.getElementById('searchBtn').addEventListener('click', searchValue);
  document.getElementById('exampleBtn').addEventListener('click', populateExample);
  document.getElementById('clearBtn').addEventListener('click', clearTree);

  keyInput.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
      insertValue();
    }
  });
});
