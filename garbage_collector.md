```C
typedef struct s_node {
    void    *data;      // pointer
}   t_node;
```

```C
// ancre du premier node de la liste

t_node  **anchor() {
    static t_node *__anchor = NULL;  // globale
    return &__anchor;
}

// setter

void    set_anchor(t_node *node) {
    (*anchor()) = node;// la valeur de anchor est node .
}

// getter

t_node  *get_anchor() {
    return (*anchor());// return le pointeur de l'ancre qui est le pointeursur le premier malloc 
}
```

```C
void    panic() {
    free_all();//quit 
    exit(1);
}

void    free_all() {
    t_node  node;
    t_node  tmp;

    node = get_anchor();
    while (node) {// parcours toute la liste chaineee et free tout blabla 
        tmp = node;
        if (tmp->data)
            free(tmp->data);
        free(tmp);
        node = tmp->next;
    }
    set_anchor(NULL);
}

// size = sizeof(....)
t_node  *new_node() {
    t_node  node;

    node = malloc(sizeof(t_node));// cree ton node contenant le pointeur du malloc en question , et le met a la fin de la liste chainee 
    if (!node)// si pas de malloc 
        panic();// free tout 
    node->data = 0;//init 

    // ajout a la fin de la liste
    t_node  __anchor;
    __anchor = get_anchor();
    if (__anchor == NULL)
        return set_anchor(node);
    while (__anchor->next)
        __anchor = _anchor->next;
    __anchor->next = node;
    return node;
}

void    *gmalloc(size_t size) {
    t_node  node;

    node = new_node();//alloue ton node qui contient le pointeur du malloc 
    
    void    *data;

    data = malloc(size);//le malloc en question 
    if (!data)
        panic();

    node->data = data;
    return data;
}

void    free(void *target) {
    t_node  node;
    t_node  tmp;

    node = get_anchor();
    while (node) {
        if (node->next->data == target) {
            tmp = node->next;
            free(tmp->data);
            free(tmp);
            node->next = node->next->next;
        }
    }
}
```