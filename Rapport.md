# Rapport TP3

---
__*Choix d'implémentation*__ 


__structure liste :__
  - Etant donné que la sentinelle existe toujours quand la liste existe j'ai décidé d'utiliser la valeur de la sentinelle pour la taille. Cela permet de gagner 4 octets (ce qui est négligable).
  - présence d'un define pour la size pour y accéder facilement

__structure Sublist :__
  - La structure est uniquement défini dans le .c car elle n'a aucun intérêt pour l'utilisateur et s'il y a accès il risque juste d'invalider les invariants comme la taille par exemple.
  - Toutes les fonctions qui utilisent la sublist sont donc inconnus à l'utilisateur et pas définis dans le .h

__Fonction void printToken(FILE* f, const void* e) :__
- Fonction map classique (complexité O(n))

__Fonction Queue* shuntingYard(Queue* infix) :__
-  *Problème rencontré :*
     - Lors de l'inplémentation de la condition ``` while (( there is an operator at the top of the operator stack with greater precedence ) or ( the operator at the top of the operator stack has equal precedence and the operator is left associative )) and ( the operator at the top of the stack is not a left bracket ) ``` pour que tous les assert soient validés il a fallut pour la dernière condition ajouter une condition ternaire ( ? : ) avec uniquement un false. Etant donné le makefile qui transforme tous les warnings en erreur la seule solution était donc ``` tokenIsParenthesis(stackTop(operator)) ? tokenGetParenthesisSymbol((stackTop(operator))) != ')' : true ```

__Fonction Token *evaluateOperator(Token *arg1, Token *op, Token *arg2) :__
- le cas où l'opérateur n'est pas pris en compte l'erreur est géré et le programme interrompu.
- Si un argument ou l'opérateur n'est pas du bon type alors l'erreur est géré et le programme interrompu.

__Fonction void computeExpressions(FILE *fd) :__ 
- gestion de l'erreur du getfile

__Fonction int main(int argc, char *argv[]) :__
- gestion de l'erreur du fclose


__*Description du comportement sur les jeux de tests fournis*__

- Tous les jeux de test ont été validés


__*Analyse personnelle du travail effectué*__

- Il subsiste toujours une fuite de mémoire (192bits) que je n'arrive pas à régler. La fuite est lié à un.
