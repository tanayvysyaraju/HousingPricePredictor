# HousePrice: C-Based Linear Regression Engine

HousePrice is a machine-learning–inspired house-price predictor implemented entirely in **C**. It models housing prices using **linear regression** solved analytically with core **linear algebra** operations like transposition, matrix multiplication, and Gauss-Jordan elimination. This project demonstrates how key supervised-learning concepts can be implemented using systems-level programming.

---

## Project Motivation

Most machine learning tools abstract away the math and memory under the hood. This project brings that machinery into view by directly implementing the regression pipeline in C:

* Performing real linear algebra without external libraries
* Managing dynamic memory and file I/O manually
* Bridging the gap between ML theory and low-level systems code

---

## Features

* **Pure C (C99) Implementation**

  * No external libraries or matrix packages

* **Matrix Operations**

  * `transpose()`
  * `multiply()`
  * `invert()` (via Gauss-Jordan elimination)

* **Robust I/O and Memory Management**

  * Dynamically reads datasets of any size
  * All memory allocated/freed manually

* **Price Prediction**

  * Computes weight vector using normal equation: `W = (X^T X)^-1 X^T Y`
  * Predicts future house prices with: `Y' = X' W`

* **Build System**

  * Clean Makefile
  * Flags: `-Wall -Werror -std=c99 -fsanitize=address,undefined`

---

## Input Format

### Training File (`train.txt`)

```
train
k            # number of attributes
n            # number of training examples
x1 ... xk y  # feature vector followed by price
```

### Data File (`data.txt`)

```
data
k            # number of attributes
m            # number of houses to predict
x1 ... xk    # feature vectors
```

---

## Setup Instructions

### Compile

```bash
cd src
make
```

### Run

```bash
./estimate train.txt data.txt
```

### Example Output

```bash
737861
203060
```

(Each line is a predicted price, rounded to the nearest dollar.)

---

## Tech Stack

| Layer         | Technology                           |
| ------------- | ------------------------------------ |
| Core Language | ANSI C99                             |
| Math Engine   | Manual linear algebra (Gauss-Jordan) |
| Tooling       | Make + GCC                           |

---

## Skills Demonstrated

* Manual implementation of **linear regression**
* Low-level **dynamic memory management**
* Use of **POSIX I/O** and `read()`/`write()` style programming
* Application of **Gauss-Jordan elimination** in C
* Full-cycle systems project from parsing to computation to output

---

## Acknowledgments

Assignment for **CS 211: Computer Architecture and Systems Programming – Fall 2024**
Instructor: **Prof. David Menendez** @ Rutgers University
