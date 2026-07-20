# Structures à choisir et prochaines étapes

## 1. Ce qui existe déjà

Le projet contient actuellement :

- une liste chaînée `t_env` pour les variables d'environnement ;
- une partie des builtins ;
- un début d'exécuteur capable de reconnaître les builtins ;
- un `main` utilisé pour tester `echo`.

Le lexer, le parser, l'expander, les signaux et l'exécution complète restent à
faire.

## 2. Structures à choisir ensemble

Avant de coder le parsing et l'exécution, il faut décider comment représenter :

- un token : mot, pipe, redirection, heredoc, etc. ;
- une commande et son tableau `argv` ;
- les redirections d'une commande ;
- une suite de commandes reliées par des pipes ;
- l'état du shell, notamment l'environnement et le dernier code de retour.

Exemple minimal à discuter :

```c
typedef struct s_token
{
    char            *value;
    int             type;
    int             was_quoted;
    struct s_token  *next;
}   t_token;

typedef struct s_cmd
{
    char            **argv;
    t_redir         *redirections;
    struct s_cmd    *next;
}   t_cmd;
```

Ces structures sont seulement des propositions. Le plus important est que le
parser produise exactement le format attendu par l'exécuteur.

## 3. Répartition possible

### Parsing

```text
ligne de readline
  -> lexer
  -> vérification de la syntaxe
  -> expansion des variables
  -> liste de commandes
```

Le parsing doit gérer les mots, les quotes, `$VAR`, `$?`, les pipes et les
redirections `<`, `>`, `<<` et `>>`.

### Exécution

```text
liste de commandes
  -> heredocs et redirections
  -> création des pipes
  -> builtin ou programme externe
  -> récupération du code de retour
```

## 4. Ce qu'il reste globalement à faire

1. Valider les structures communes dans `minishell.h`.
2. Écrire les fonctions qui libèrent ces structures.
3. Implémenter le lexer, le parser et l'expansion.
4. Terminer `export` et implémenter `exit`.
5. Exécuter les programmes externes en utilisant `PATH` et `execve`.
6. Ajouter les pipes, redirections et heredocs.
7. Créer la vraie boucle `readline` dans le `main`.
8. Gérer `Ctrl-C`, `Ctrl-D` et `Ctrl-\`.
9. Ajouter les nouveaux fichiers au Makefile.
10. Tester les erreurs, les codes de retour et les fuites mémoire.

## 5. Première décision à prendre

La première réunion doit répondre à cette question :

> Quelle structure exacte le parser transmet-il à l'exécuteur ?

Une fois `t_token`, `t_cmd` et les redirections validés, chacun peut travailler
sur sa partie sans créer d'incompatibilité.
