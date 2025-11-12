# vbc

### 🧮 Expression Evaluator (42 Exam Project)

`vbc` is a small recursive parser and evaluator written in C.  
It takes a **mathematical expression** as an argument and prints the **computed result**.

The program supports:
- Addition (`+`)
- Multiplication (`*`)
- Parentheses (`(` and `)`)

All numbers must be **between 0 and 9** (single digits).

---

## 💡 Example Usage

```bash
$ ./vbc "1"
1

$ ./vbc "2+3"
5

$ ./vbc "3*4+5"
17

$ ./vbc "3+4*5"
23

$ ./vbc "(3+4)*5"
35

$ ./vbc "(((((2+2)*2+2)*2+2)*2+2)*2+2)*2"
188



Tips in french:
- Analyse syntaxique récursive descendante

🔹 Traduction “humaine” :

Une expression = une somme de plusieurs produits.

Un produit = une suite de multiplications de facteurs.

Un facteur = soit un nombre, soit une expression entre parenthèses.