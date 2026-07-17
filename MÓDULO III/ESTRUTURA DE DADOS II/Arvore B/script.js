// Este arquivo implementa uma B-Tree em JavaScript.
// Comentários em português explicam cada classe e método.

// Nó da B-Tree: armazena múltiplas chaves e ponteiros para filhos.
class BTreeNode {
  // t: grau mínimo da B-Tree; leaf: se o nó é folha
  constructor(t, leaf = false) {
    this.t = t;
    this.leaf = leaf;
    // Array de chaves ordenadas no nó
    this.keys = [];
    // Array de ponteiros para filhos (length = keys.length + 1 quando não-folha)
    this.children = [];
  }

  // Retorna true se o nó está cheio (máximo de chaves).
  isFull() {
    return this.keys.length === 2 * this.t - 1;
  }

  // Busca recursiva: procura uma chave dentro do nó ou desce para o filho correto.
  // Retorna o nó onde a chave foi encontrada ou null se não existir.
  search(key) {
    let idx = 0;
    // Avança até encontrar uma chave maior ou igual à desejada
    while (idx < this.keys.length && key > this.keys[idx]) {
      idx++;
    }
    // Se a chave estiver no nó, retorna o nó atual
    if (idx < this.keys.length && this.keys[idx] === key) {
      return this;
    }
    // Se for folha e não encontrou, não existe na árvore
    if (this.leaf) {
      return null;
    }
    // Senão, desce recursivamente para o filho apropriado
    return this.children[idx].search(key);
  }

  // Percorre em-ordem (in-order) agregando chaves no array 'result'.
  // Em B-Tree, para cada chave i: percorre child[i], adiciona key[i], depois child[last].
  traverse(result = []) {
    for (let i = 0; i < this.keys.length; i++) {
      if (!this.leaf) {
        this.children[i].traverse(result);
      }
      result.push(this.keys[i]);
    }
    if (!this.leaf) {
      // último filho à direita
      this.children[this.keys.length].traverse(result);
    }
    return result;
  }
}

// Classe principal da B-Tree com operações públicas: search, insert, delete, clear.
class BTree {
  // t: grau mínimo (padrão 2). Uma B-Tree de grau t tem entre t-1 e 2t-1 chaves por nó.
  constructor(t = 2) {
    this.t = t;
    // Inicializa árvore com uma raiz folha vazia
    this.root = new BTreeNode(t, true);
  }

  // Busca uma chave na árvore; retorna o nó onde a chave foi encontrada ou null.
  search(key) {
    if (!this.root) {
      return null;
    }
    return this.root.search(key);
  }

  // Insere uma chave única na árvore; retorna false se já existir.
  insert(key) {
    if (this.search(key)) {
      // Evita chaves duplicadas
      return false;
    }

    const r = this.root;
    // Se raiz cheia, cria novo nó e divide
    if (r.isFull()) {
      const s = new BTreeNode(this.t, false);
      // antigo root torna-se filho 0 do novo nó s
      s.children[0] = r;
      this.splitChild(s, 0);
      this.root = s;
      this.insertNonFull(s, key);
    } else {
      // Se não cheia, insere diretamente
      this.insertNonFull(r, key);
    }
    return true;
  }

  // Inserção em nó que não está cheio. Percorre até a folha correta e insere ordenado.
  insertNonFull(node, key) {
    let i = node.keys.length - 1;
    if (node.leaf) {
      // Desloca chaves maiores e insere a nova na posição correta
      while (i >= 0 && key < node.keys[i]) {
        i--;
      }
      node.keys.splice(i + 1, 0, key);
    } else {
      // Encontra o filho apropriado para descer
      while (i >= 0 && key < node.keys[i]) {
        i--;
      }
      i += 1;
      // Se o filho está cheio, divide-o primeiro
      if (node.children[i].isFull()) {
        this.splitChild(node, i);
        // Após dividir, decide qual dos dois filhos deve receber a chave
        if (key > node.keys[i]) {
          i += 1;
        }
      }
      this.insertNonFull(node.children[i], key);
    }
  }

  // Divide o filho 'child' do 'parent' no índice 'index'.
  // Move a chave do meio para o parent e cria um irmão (sibling).
  splitChild(parent, index) {
    const t = this.t;
    const child = parent.children[index];
    const sibling = new BTreeNode(t, child.leaf);

    // sibling recebe as chaves da posição t..end do child
    sibling.keys = child.keys.splice(t);
    // A chave do meio (nova raiz do segmento) é a última chave restante em child
    const middleKey = child.keys.pop();

    // Se não for folha, move os ponteiros correspondentes
    if (!child.leaf) {
      sibling.children = child.children.splice(t);
    }

    // Insere o sibling como filho imediato após 'child'
    parent.children.splice(index + 1, 0, sibling);
    // Insere a chave do meio no parent na posição 'index'
    parent.keys.splice(index, 0, middleKey);
  }

  // Remove uma chave da árvore; retorna true se removida.
  delete(key) {
    if (!this.root) {
      return false;
    }
    const removed = this.deleteFromNode(this.root, key);
    // Ajuste da raiz: se ficar vazia, escolhe novo root correto
    if (this.root.keys.length === 0 && !this.root.leaf) {
      this.root = this.root.children[0];
    }
    if (this.root.keys.length === 0 && this.root.leaf) {
      // Mantém uma raiz válida (folha vazia)
      this.root = new BTreeNode(this.t, true);
    }
    return removed;
  }

  // Remoção recursiva a partir de um nó dado.
  deleteFromNode(node, key) {
    const idx = this.findKey(node, key);

    // Se a chave está no nó
    if (idx < node.keys.length && node.keys[idx] === key) {
      if (node.leaf) {
        // Caso simples: remover da folha
        node.keys.splice(idx, 1);
        return true;
      }
      // Chave em nó interno: tratar casos especiais
      return this.deleteInternal(node, key, idx);
    }

    // Se é folha e não encontrou, não está na árvore
    if (node.leaf) {
      return false;
    }

    // Determina se descer para o último filho (flag)
    let flag = idx === node.keys.length;
    // Garante que o filho escolhido tenha pelo menos t chaves antes de descer
    if (node.children[idx].keys.length < this.t) {
      this.fill(node, idx);
    }

    // Após ajustes, decide para qual filho descer
    if (flag && idx > node.keys.length) {
      return this.deleteFromNode(node.children[idx - 1], key);
    }
    return this.deleteFromNode(node.children[idx], key);
  }

  // Remoção quando a chave está em um nó interno (idx aponta para a chave)
  deleteInternal(node, key, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    // Se o predecessor (filho à esquerda) tem >= t chaves, substitui pela predecessor
    if (child.keys.length >= this.t) {
      const pred = this.getPredecessor(child);
      node.keys[idx] = pred;
      return this.deleteFromNode(child, pred);
    }

    // Senão, se o sucessor (filho à direita) tem >= t chaves, usa o sucessor
    if (sibling.keys.length >= this.t) {
      const succ = this.getSuccessor(sibling);
      node.keys[idx] = succ;
      return this.deleteFromNode(sibling, succ);
    }

    // Caso ambos tenham t-1 chaves: mescla e continua remoção
    this.merge(node, idx);
    return this.deleteFromNode(child, key);
  }

  // Retorna o índice da primeira chave >= key dentro de node
  findKey(node, key) {
    let idx = 0;
    while (idx < node.keys.length && node.keys[idx] < key) {
      idx += 1;
    }
    return idx;
  }

  // Obtém o predecessor (maior chave à esquerda) no sub-árvore fornecida
  getPredecessor(node) {
    let current = node;
    while (!current.leaf) {
      current = current.children[current.keys.length];
    }
    return current.keys[current.keys.length - 1];
  }

  // Obtém o sucessor (menor chave à direita) no sub-árvore fornecida
  getSuccessor(node) {
    let current = node;
    while (!current.leaf) {
      current = current.children[0];
    }
    return current.keys[0];
  }

  // Garante que child[idx] tenha pelo menos t chaves antes de descer para ele
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

  // Move uma chave do irmão esquerdo para o filho[idx]
  borrowFromPrev(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx - 1];

    // Insere a chave do parent no início de child
    child.keys.unshift(node.keys[idx - 1]);
    if (!child.leaf) {
      // Move também o ponteiro filho mais à direita do sibling
      child.children.unshift(sibling.children.pop());
    }

    // Atualiza a chave do parent a partir do sibling
    node.keys[idx - 1] = sibling.keys.pop();
  }

  // Move uma chave do irmão direito para o filho[idx]
  borrowFromNext(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    // Puxa a chave do parent para o fim de child
    child.keys.push(node.keys[idx]);
    if (!child.leaf) {
      // Move também o primeiro ponteiro de sibling para child
      child.children.push(sibling.children.shift());
    }

    // Atualiza a chave do parent a partir do sibling
    node.keys[idx] = sibling.keys.shift();
  }

  // Mescla child[idx] e child[idx+1] e desloca a chave parent.keys[idx] para o filho resultante
  merge(node, idx) {
    const child = node.children[idx];
    const sibling = node.children[idx + 1];

    child.keys.push(node.keys[idx], ...sibling.keys);
    if (!child.leaf) {
      child.children.push(...sibling.children);
    }

    // Remove a chave do parent e o ponteiro para sibling
    node.keys.splice(idx, 1);
    node.children.splice(idx + 1, 1);
  }

  // Retorna as chaves da árvore em ordem
  inorder() {
    return this.root.traverse([]);
  }

  // Limpa a árvore, atribuindo uma raiz folha vazia
  clear() {
    this.root = new BTreeNode(this.t, true);
  }
}

// Instância da B-Tree usada pela interface (grau mínimo t = 2)
const tree = new BTree(2);
// Elementos do DOM usados pela interface
const keyInput = document.getElementById('keyInput');
const treeRoot = document.getElementById('treeRoot');
const status = document.getElementById('status');

// Atualiza a área de status com uma mensagem amigável
function setStatus(message) {
  status.textContent = message;
}

// Gera recursivamente o HTML que representa um nó da B-Tree
function renderTree(node) {
  if (!node) {
    return null;
  }

  const wrapper = document.createElement('div');
  wrapper.className = 'tree-node-group';

  // Caixa que mostra todas as chaves do nó separadas por | para legibilidade
  const nodeBox = document.createElement('div');
  nodeBox.className = 'node';
  nodeBox.textContent = node.keys.join(' | ');
  wrapper.appendChild(nodeBox);

  // Se não for folha, renderiza também os filhos abaixo do nó
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

// Renderiza a árvore inteira no elemento `treeRoot` do DOM
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

// Lê o valor do input, valida inteiro e insere na B-Tree
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

// Lê o valor do input, valida e remove da B-Tree
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

// Busca um valor e atualiza a área de status informando se foi encontrado
function searchValue() {
  const value = Number(keyInput.value);
  if (!Number.isInteger(value)) {
    setStatus('Digite um número inteiro válido.');
    return;
  }

  const found = tree.search(value);
  setStatus(found ? `Valor ${value} encontrado.` : `Valor ${value} não encontrado.`);
}

// Popula a B-Tree com um exemplo de valores para demonstração
function populateExample() {
  tree.clear();
  [10, 20, 5, 6, 12, 30, 7, 17].forEach((value) => tree.insert(value));
  render();
  setStatus(`Exemplo carregado. Ordem: ${tree.inorder().join(' -> ')}`);
}

// Limpa a árvore e atualiza a interface
function clearTree() {
  tree.clear();
  render();
  setStatus('Árvore limpa.');
}

// Conecta os eventos do DOM às funções acima quando o documento estiver pronto
window.addEventListener('DOMContentLoaded', () => {
  render();
  document.getElementById('insertBtn').addEventListener('click', insertValue);
  document.getElementById('deleteBtn').addEventListener('click', deleteValue);
  document.getElementById('searchBtn').addEventListener('click', searchValue);
  document.getElementById('exampleBtn').addEventListener('click', populateExample);
  document.getElementById('clearBtn').addEventListener('click', clearTree);

  // Permite inserir com Enter no campo de input
  keyInput.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
      insertValue();
    }
  });
});
