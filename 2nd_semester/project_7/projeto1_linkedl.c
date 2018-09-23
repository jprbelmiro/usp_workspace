//ESTRUTURAS ------------------------------------------------------------------
struct node{
    char *host_name;
    char *host_ip;
    struct node *next;
};

struct linkedlist{
  struct node *start;
  int list_len;
};

//FUNCOES ----------------------------------------------------------------------
void free_linkedl(struct linkedlist *list){
    if(list->start == NULL){
        free(list);
        return;
    }
    list->list_len -= 1;
    
    if(list->start->host_name != NULL)
        free(list->start->host_name);
    if(list->start->host_ip != NULL)
        free(list->start->host_ip);
    
    struct node *aux = list->start->next;
    free(list->start);
    list->start = aux;
    free_linkedl(list);
}

struct node *create_linkedl_node(struct node *next, char *name, char *ip){
    struct node *node = (struct node *)malloc(sizeof(struct node));
    
    if(name != NULL){
        node->host_name = stringcopy(name);
    }
    else node->host_name = NULL;
    
    if(ip != NULL){
        node->host_ip = stringcopy(ip);
    }
    else node->host_ip = NULL;
    
    node->next = next;
    return node;
}

struct linkedlist *create_linkedl(){
    struct linkedlist *linkedl = 
        (struct linkedlist *)malloc(sizeof(struct linkedlist));
    linkedl->start = NULL;
    linkedl->list_len = 0;
    return linkedl;
}

void insert_linkedlist(struct linkedlist *linkedl, char *host_name, char *host_ip){
    if(linkedl->list_len == 0){
        struct node *node = create_linkedl_node(NULL,host_name,host_ip);
        linkedl->start = node;
        linkedl->list_len += 1;
        return;
    }
    else{
        struct node *node = create_linkedl_node(linkedl->start,host_name,host_ip);
        linkedl->start = node;
        linkedl->list_len += 1;
        return;        
    }
}

void search_linkedlist(struct node *node, char *name){
    if(node == NULL){
        printf("-1\n");
        return;
    }
    if(strcmp(node->host_name,name)==0){
        printf("%s\n",node->host_ip);
        return;
    }
    
    return search_linkedlist(node->next,name);
}

void delete_linkedlist(struct node *node, char *name, struct node *prev, struct linkedlist * linkedl){
    if(node == NULL)
        return;
        
    if(strcmp(node->host_name,name)==0){
        if(prev == NULL)
            linkedl->start = node->next;
        else
            prev->next = node->next;
            
        free(node->host_name);
        free(node->host_ip);
        free(node);
        return;
    }
    
    return delete_linkedlist(node->next,name,node,linkedl);    
}