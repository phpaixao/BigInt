# 🔢 BigInt – Inteiros de Valor Máximo Ilimitado

![C++](https://img.shields.io/badge/language-C%2B%2B11-blue)
![Status](https://img.shields.io/badge/status-finished-brightgreen)
![License](https://img.shields.io/badge/license-academic-lightgrey)

Projeto desenvolvido na disciplina de **Programação em C++** (UFRN), com o objetivo de implementar uma classe `BigInt` capaz de representar e manipular números inteiros **positivos, negativos ou nulos** com **quantidade ilimitada de dígitos**.

---

## 📌 Sobre o Projeto
A classe `BigInt` foi implementada em **C++ puro**, utilizando apenas:
- Ponteiros convencionais e **alocação dinâmica de memória** (`new` e `delete`);
- Construtores, destrutores e sobrecarga de operadores;
- Divisão do código em arquivos `.h` e `.cpp`.

O projeto foi desenvolvido seguindo as boas práticas da disciplina, sem o uso de **templates, STL containers (vector, pair, etc.), exceções, herança ou métodos virtuais**.

---

## ⚙️ Funcionalidades Implementadas

A classe `BigInt` oferece:
- **Construtores**
  - Default (`0`);
  - A partir de `long long int`;
  - A partir de `std::string`;
  - Cópia e movimento.
- **Entrada e saída**
  - `operator<<` para impressão;
  - `operator>>` para leitura formatada.
- **Operações matemáticas**
  - Adição (`+`) e subtração (`-`);
  - Multiplicação (`*`);
  - Divisão inteira (`/` e `%`);
  - Fatorial (`!`);
  - Incremento/Decremento (pré e pós).
- **Operações auxiliares**
  - Valor absoluto (`abs`);
  - Negação unária (`-X`);
  - Comparações (`==`, `!=`, `<`, `<=`, `>`, `>=`);
  - Deslocamento de dígitos (`<<` e `>>`).
- **Conversões**
  - Para `long long int` (com verificação de limites).
- **Correção automática**
  - Ajuste de dígitos inválidos ou zeros à esquerda.

---

## 🖥️ Mini-Calculadora

A classe `BigInt` foi testada em um programa principal fornecido pelo professor: uma **mini-calculadora de BigInt**, capaz de:

- Somar, subtrair, multiplicar e dividir inteiros arbitrários;
- Calcular resto e quociente;
- Calcular fatorial;
- Incrementar/decrementar valores;
- Alterar sinal ou calcular valor absoluto;
- Realizar rotações de dígitos.

---

## 🚀 Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/SEU-USUARIO/BigInt.git
   cd BigInt
   ```

2. Compile o projeto:
   ```bash
   g++ -std=c++11 -Wall mainteste.cpp BigInt.cpp -o bigint
   ```

3. Execute a mini-calculadora:
   ```bash
   ./bigint
   ```

---

## 🛠️ Tecnologias Utilizadas
- **C++11**
- Compilador `g++`
- Programação orientada a objetos
- Gerenciamento manual de memória

---

## 📚 Aprendizados
- Implementação de estruturas de dados com **alocação dinâmica**;
- Manipulação de **grandes números inteiros** sem depender de bibliotecas externas;
- Exercício prático de **sobrecarga de operadores** em C++;
- Organização de projetos em múltiplos arquivos.

---

## ⚠️ Aviso Importante
Este projeto fez parte de uma **avaliação da disciplina de Programação Avançada (DCA3303 - UFRN)**.  
O código foi submetido a um **software detector de plágio**.  

👉 **Não é recomendado copiar qualquer trecho deste repositório para fins acadêmicos**, pois isso pode ser facilmente detectado.

---

## 📄 Licença
Este projeto foi desenvolvido para fins acadêmicos na UFRN.  
Você pode usar o código para estudo ou referência livremente.
