# Minitalk - Proyecto de la Escuela 42

## Descripción

**Minitalk** es un proyecto simple de comunicación cliente-servidor donde debes implementar un sistema de comunicación utilizando señales de UNIX. El cliente envía una cadena de caracteres al servidor, carácter por carácter, y el servidor la muestra en su terminal.

Este proyecto sirve como una introducción al manejo de señales en sistemas basados en Unix, centrándose en conceptos como la gestión de señales y operaciones bit a bit.

## Características

- Comunicación entre cliente y servidor utilizando **solo dos señales**:
  - `SIGUSR1` para el bit 0.
  - `SIGUSR2` para el bit 1.
- Envío de cadenas de cualquier longitud desde el cliente al servidor.
- El servidor reconoce y muestra el mensaje recibido en tiempo real.
- Maneja casos especiales como entradas nulas y caracteres especiales.

## Requisitos

- El proyecto debe utilizar **únicamente señales de UNIX** para la comunicación.
- No se permiten bibliotecas externas ni multi-threading.
- El cliente debe ser capaz de enviar mensajes al servidor, que los imprimirá en la terminal.
- Tanto el cliente como el servidor deben ser **resistentes** a interrupciones de señal y manejar entradas inesperadas de manera adecuada.
