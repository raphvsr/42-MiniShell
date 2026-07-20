# Guide du projet Minishell pour le parsing

## 1. Objectif du projet

Minishell doit reproduire une petite partie du comportement de Bash.

Le programme doit :

- afficher un prompt et lire une ligne avec `readline` ;
- comprendre les commandes et leurs arguments ;
- gérer les quotes simples et doubles ;
- développer les variables d'environnement comme `$USER` et `$?` ;
- gérer les redirections `<`, `>`, `<<` et `>>` ;
- connecter plusieurs commandes avec des pipes `|` ;
- exécuter les builtins ou des programmes externes.

Le parsing fait le pont entre la ligne écrite par l'utilisateur et
l'exécuteur.

## 2. Fonctionnement général

```text
readline
   |
   v
lexer
   |
   v
liste de tokens
   |
   v
validation syntaxique et parser
   |
   v
expansion des variables
   |
   v
liste de commandes
   |
   v
redirections, pipes et exécution
```

Exemple de ligne saisie :

```bash
cat < input.txt | grep "$USER" >> result.txt
```

Le lexer devrait produire une suite proche de :

```text
WORD(cat)
REDIR_IN(<)
WORD(input.txt)
PIPE(|)
WORD(grep)
WORD($USER, double quotes)
APPEND(>>)
WORD(result.txt)
```

Le parser devrait ensuite construire :

```text
Commande 1
  argv = ["cat"]
  entrée = "input.txt"
  pipe vers la commande suivante

Commande 2
  argv = ["grep", valeur de $USER]
  sortie = "result.txt"
  mode = append
```

## 3. Structure actuelle du dépôt

```text
42-MiniShell/
|-- Makefile
|-- libft/
|-- src/
|   |-- main.c
|   |-- minishell.h
|   |-- builtins/
|   |-- env/
|   |-- errors/
|   |-- exec/
|   |-- parsing/
|   |   |-- lexer/
|   |   |-- parser/
|   |   |-- expander/
|   |-- signals/
```

### `src/main.c`

Le `main` est actuellement un programme de test pour `echo`.

La future version devra notamment :

1. initialiser la copie de l'environnement ;
2. configurer les signaux ;
3. appeler `readline` dans une boucle ;
4. envoyer la ligne au parsing ;
5. envoyer le résultat à l'exécuteur ;
6. libérer les structures créées à chaque tour.

### `src/builtins/`

Ce dossier contient les commandes internes du shell :

- `echo` : présent, avec l'option `-n` ;
- `pwd` : présent ;
- `env` : présent ;
- `unset` : présent ;
- `cd` : présent avec un chemin, et mise à jour de `PWD` et `OLDPWD` ;
- `export` : encore incomplet ;
- `exit` : pas encore implémenté.

Les builtins reçoivent généralement un tableau terminé par `NULL` :

```c
char *args[] = {"echo", "hello", "world", NULL};
```

Le parser doit donc produire un `argv` sous cette forme pour chaque commande.

### `src/env/`

Les variables d'environnement sont stockées dans une liste chaînée :

```c
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;
```

Par exemple, la chaîne :

```text
USER=raph
```

devient un nœud contenant :

```text
key   = "USER"
value = "raph"
```

Cette liste permettra à l'expander de chercher la valeur d'une variable.

### `src/exec/executor.c`

L'exécuteur reconnaît déjà le nom des builtins à partir de `args[0]`.

Il ne gère pas encore :

- les programmes externes avec `execve` ;
- la recherche dans `PATH` ;
- les pipes ;
- les redirections ;
- les heredocs.

### `src/parsing/`

Les fichiers suivants sont encore vides :

- `lexer/lexer.c` ;
- `parser/parser.c` ;
- `expander/expander.c`.

Leur interface et les structures communes doivent être définies avant de
commencer leur implémentation.

### `Makefile`

Le Makefile compile actuellement le `main`, l'environnement et les builtins.
Il faudra ajouter les fichiers du parsing, de l'exécution et des signaux dans
la variable `SRCS` lorsqu'ils seront utilisés.

## 4. Travail du lexer

Le lexer lit la ligne caractère par caractère et la découpe en tokens.

Il doit reconnaître au minimum :

| Élément | Type de token proposé |
|---|---|
| texte ou argument | `TOKEN_WORD` |
| `|` | `TOKEN_PIPE` |
| `<` | `TOKEN_REDIR_IN` |
| `>` | `TOKEN_REDIR_OUT` |
| `<<` | `TOKEN_HEREDOC` |
| `>>` | `TOKEN_APPEND` |

Une structure possible est :

```c
typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;
```

Cette structure est une proposition : elle doit être validée ensemble avant
d'être utilisée.

### Gestion des espaces

En dehors des quotes, un espace sépare normalement deux mots :

```bash
echo hello world
```

devient :

```text
WORD(echo) WORD(hello) WORD(world)
```

Dans des quotes, l'espace appartient au même argument :

```bash
echo "hello world"
```

doit produire :

```c
{"echo", "hello world", NULL}
```

### Gestion des opérateurs collés aux mots

Les opérateurs doivent être reconnus même sans espaces :

```bash
cat<input.txt|wc -l>>result.txt
```

### Gestion des quotes

Les quotes servent à protéger leur contenu :

```bash
echo 'hello | world'
echo "hello > world"
```

Dans ces exemples, `|` et `>` sont du texte, pas des opérateurs.

Le lexer doit également détecter une quote non fermée :

```bash
echo "hello
```

Le sujet demande de ne pas interpréter une ligne qui contient des quotes non
fermées.

## 5. Travail du parser

Le parser reçoit les tokens produits par le lexer.

Il doit :

- vérifier la syntaxe ;
- regrouper les mots dans le tableau `argv` d'une commande ;
- associer une redirection à son fichier ou à son délimiteur ;
- créer une nouvelle commande après chaque pipe ;
- fournir à l'exécuteur une structure facile à parcourir.

### Erreurs de syntaxe à détecter

Exemples invalides :

```bash
| echo hello
echo hello |
cat >
cat < | wc
echo hello || wc
```

Règles principales :

- un pipe doit avoir une commande à gauche et à droite ;
- une redirection doit être suivie d'un `WORD` ;
- deux pipes consécutifs ne font pas partie du sujet obligatoire ;
- une ligne invalide ne doit pas être exécutée.

## 6. Structure proposée pour une commande

Le parser pourrait produire une liste chaînée de commandes :

```c
typedef struct s_redir
{
    t_token_type    type;
    char            *target;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **argv;
    t_redir         *redirections;
    struct s_cmd    *next;
}   t_cmd;
```

Dans cette proposition :

- `argv` contient le programme et ses arguments ;
- `redirections` contient toutes les redirections de la commande ;
- `next` désigne la commande suivante dans le pipeline.

Exemple :

```bash
grep hello < input.txt | wc -l > output.txt
```

pourrait donner :

```text
t_cmd 1
  argv = ["grep", "hello", NULL]
  redirections = [REDIR_IN, "input.txt"]
  next -----------+
                   |
                   v
t_cmd 2
  argv = ["wc", "-l", NULL]
  redirections = [REDIR_OUT, "output.txt"]
  next = NULL
```

## 7. Expansion des variables

L'expander remplace les variables par leurs valeurs.

```bash
echo $USER
echo "$USER"
echo $?
```

- `$USER` devient la valeur de `USER` dans `t_env` ;
- `$?` devient le code de retour de la dernière pipeline exécutée ;
- une variable inexistante devient généralement une chaîne vide.

### Effet des quotes

```bash
echo '$USER'
```

Les simples quotes empêchent toute expansion. La commande affiche donc
littéralement `$USER`.

```bash
echo "$USER"
```

Les doubles quotes protègent les espaces et les métacaractères, mais autorisent
l'expansion de `$`.

Il faut donc conserver suffisamment d'informations sur les quotes jusqu'à
l'expansion. Les supprimer dès le début du lexer ferait perdre cette
information.

### Cas particulier du heredoc

```bash
cat << EOF
cat << 'EOF'
```

Le délimiteur doit être conservé sans ses quotes pour savoir quand arrêter le
heredoc. Cependant, la présence de quotes doit également être mémorisée : un
délimiteur quoté désactive l'expansion des variables dans le contenu du
heredoc.

Une simple chaîne `value` dans `t_token` risque donc de ne pas suffire. Il peut
être utile d'ajouter une information comme :

```c
int was_quoted;
```

ou de conserver un état de quote plus précis dans les fragments du mot.

## 8. Contrat entre parsing et exécution

Avant de coder, il faut définir exactement ce que le parser transmet à
l'exécuteur.

Une interface possible serait :

```c
t_cmd *parse_line(char *line, t_env *env, int last_status);
```

L'exécuteur pourrait ensuite proposer :

```c
int execute_commands(t_cmd *commands, t_env **env);
```

Répartition possible :

```text
Parsing
  ligne
    -> tokens
    -> validation
    -> expansion
    -> liste de t_cmd

Exécution
  liste de t_cmd
    -> heredocs
    -> pipes
    -> redirections
    -> builtin ou execve
    -> code de retour
```

Il faut aussi décider qui est propriétaire de chaque allocation et qui la
libère. Une règle simple serait : le parsing alloue toute la liste `t_cmd`, et
le `main` la libère après l'exécution.

## 9. Informations globales du shell

Le projet aura probablement besoin d'une structure centrale contenant au
minimum :

```c
typedef struct s_shell
{
    t_env   *env;
    int     last_status;
}   t_shell;
```

`last_status` est nécessaire pour développer `$?`.

Le sujet autorise au maximum une variable globale pour mémoriser le numéro du
signal reçu. La structure complète du shell ne doit donc pas être globale.

## 10. Questions à régler ensemble avant l'implémentation

1. Quelle est la structure exacte de `t_token` ?
2. Comment conserve-t-on l'état des quotes jusqu'à l'expansion ?
3. L'expansion a-t-elle lieu pendant le lexer ou après la validation ?
4. Quelle est la structure exacte de `t_cmd` ?
5. Comment représente-t-on plusieurs redirections sur une commande ?
6. Qui prépare et lit les heredocs ?
7. Qui alloue et qui libère les tokens et les commandes ?
8. Quel code de retour est utilisé lors d'une erreur de syntaxe ?

## 11. État actuel et prochaines étapes

Le projet est actuellement une base de travail, pas encore un minishell
fonctionnel.

Ordre conseillé pour avancer :

1. valider ensemble les structures `t_token`, `t_redir`, `t_cmd` et `t_shell` ;
2. écrire les fonctions de libération correspondantes ;
3. implémenter et tester le lexer seul ;
4. ajouter la validation syntaxique ;
5. construire les commandes avec le parser ;
6. implémenter l'expansion avec les règles de quotes ;
7. brancher le résultat sur l'exécuteur ;
8. ajouter tous les fichiers au Makefile ;
9. tester les fuites et comparer les comportements demandés avec Bash.

Le point le plus important est de valider le format de `t_cmd` avant de coder
le parser et l'exécuteur. Les deux parties pourront ainsi évoluer sans devenir
incompatibles.
