# PixTerm (Pixel Terminal) 🚀 [Vídeo de apresentação] (https://youtu.be/SO7VelBtSJQ)

## 📌 Descrição do Projeto

O **PixTerm** (Pixel Terminal) é um projeto que roda na placa **BitDogLab** e se comunica via **UART** a um baudrate de **115200** com um computador via **USB**. O sistema permite a entrada de caracteres únicos pelo terminal, imprimindo-os em um **display OLED 128x64** conectado via **I2C**. Além disso, quando um número é enviado via UART, ele é impresso tanto no **display OLED** quanto na **matriz de LEDs WS2812B**.

O código foi desenvolvido em **C11** utilizando o **pico-sdk versão 2.1.0**, compilado com **GNU-ARM-EABI**, e pode ser executado no **VS Code** com as extensões **Raspberry Pi Pico** e **CMake**.

## 🔩 Componentes Utilizados

Os seguintes componentes estão conectados à placa **BitDogLab**:

- 💡 **Matriz 5x5 de LEDs WS2812B** (endereçáveis) conectada à **GPIO 7**.
- 🌈 **LED RGB** com pinos conectados às **GPIOs 11, 12 e 13**.
- 🔘 **Botão A** conectado à **GPIO 5**.
- 🔘 **Botão B** conectado à **GPIO 6**.
- 🖥️ **Display SSD1306** conectado via **I2C (GPIO 14 e GPIO 15)**.

## ⚙️ Funcionalidades do Projeto

### 1️⃣ Modificação da Biblioteca `font.h`

- 🔤 Adicionar caracteres **minúsculos** à biblioteca `font.h`. Use criatividade para criar os novos caracteres.

### 2️⃣ Entrada de Caracteres via PC 💻

- Utilize o **Serial Monitor** do VS Code para digitar os caracteres.
- Cada caractere digitado deve ser exibido no **display SSD1306**.
  - **📌 Obs.:** Apenas um caractere será enviado de cada vez, não há suporte para envio de strings completas.
- Quando um **número entre 0 e 9** for digitado, um **símbolo correspondente** deve ser exibido na **matriz 5x5 WS2812B**.

### 3️⃣ Interação com o Botão A 🔘

- Pressionar o **Botão A** alterna o estado do **LED RGB Verde (ligado/desligado) 🟢**.
- O estado do LED é registrado de duas formas:
  1. 📟 Uma **mensagem informativa** no **display SSD1306**.
  2. 📨 Um **texto descritivo** enviado ao **Serial Monitor**.

### 4️⃣ Interação com o Botão B 🔘

- Pressionar o **Botão B** alterna o estado do **LED RGB Azul (ligado/desligado) 🔵**.
- O estado do LED é registrado de duas formas:
  1. 📟 Uma **mensagem informativa** no **display SSD1306**.
  2. 📨 Um **texto descritivo** enviado ao **Serial Monitor**.

## 📝 Exemplos de Uso

### 📟 Enviar um caractere via UART

Digite um caractere no **Serial Monitor**:

```sh
A
```

Saída esperada no **display OLED**:

```
A
```

### 🔢 Enviar um número via UART

Digite um número no **Serial Monitor**:

```sh
5
```

Saída esperada no **display OLED**:

```
5
```

Além disso, o número **5** será exibido na **matriz de LEDs WS2812B**.

### 🔘 Alternar o LED Verde (Botão A - GPIO 5)

Pressione o **Botão A**.

Saída esperada:
- **LED Verde** 🟢 será ligado/desligado.

- No **display OLED**:
  ```
  LED Verde: ON
  ```
- No **Serial Monitor**:
  ```sh
  LED Verde ligado.
  ```

### 🔘 Alternar o LED Azul (Botão B - GPIO 6)

Pressione o **Botão B**.

Saída esperada:
- **LED Azul** 🔵 será ligado/desligado.
- No **display OLED**:
  ```
  LED Azul: OFF
  ```
- No **Serial Monitor**:
  ```sh
  LED Azul desligado.
  ```

### 🔄 Pressionar Ambos os Botões

Pressione **Botão A** e **Botão B** ao mesmo tempo.

Saída esperada:
- No **display OLED**:
  ```
  LED Verde: ON
  LED Azul: ON
  ```
- No **Serial Monitor**:
  ```sh
  LED Verde ligado.
  LED Azul ligado.
  ```

## 🚀 Instalação e Execução

### 🛠️ Passo 1: Clonar o Repositório

```sh
git clone https://github.com/seu-usuario/PixTerm.git
cd PixTerm
```

### 🖥️ Passo 2: Configurar o Ambiente no VS Code

1. Instale as extensões **Raspberry Pi Pico** e **CMake** no **VS Code**.
2. Abra o projeto clonado no VS Code.
3. Conecte a placa **BitDogLab** ao computador no **modo BOOTSEL**.

### ▶️ Passo 3: Compilar e Executar o Projeto

1. Compile o código utilizando o **pico-sdk**.
2. Faça o upload do firmware para a placa.
3. Abra o **Serial Monitor** no VS Code para interação com o PixTerm.

---

## 📜 Licença

Este projeto é distribuído sob a **Licença MIT**. Sinta-se livre para usá-lo, modificá-lo e distribuí-lo conforme necessário.

---

### 📩 Contato

Caso tenha dúvidas ou sugestões, entre em contato pelo e-mail **<cvaladao@ecomp.uefs.br>** ou abra uma issue no repositório GitHub.

---

### 👨‍💻 Autor

Desenvolvido por **[Carlos Valadão]**. 🚀
