#define SKIPLIST_MIN_NAME "aaa.aaaaaaaaaaaaaaa.aaa"
#define SKIPLIST_MAX_NAME "zzz.zzzzzzzzzzzzzzz.zzz"
#define SKIPLIST_MAX_LEVEL(n) (log(n)/log(2))+1

//ESTRUTURAS -------------------------------------------------------------------
struct snode{
    char *host_name;
    char *host_ip;
    struct snode *next;
    struct snode *downlvl;
};

struct skiplist{
    int size;
    int nlevel;
    struct snode **start;
};

//FUNCOES ----------------------------------------------------------------------
void free_skipl(struct skiplist *list, struct snode *node, int level){
    if(level == 0 && node == NULL){
        free(list->start);
        free(list);
        return;
    }

    if(node == NULL)
        return free_skipl(list,list->start[level-1],level-1);

    list->start[level] = node->next;
    if((strcmp(node->host_name,SKIPLIST_MAX_NAME)==0 && level == 0) || strcmp(node->host_name,SKIPLIST_MAX_NAME)<0 ){
        if(node->host_ip != NULL)free(node->host_ip);
        if(node->host_name != NULL)free(node->host_name);
        if(node != NULL)free(node);
    }

    return free_skipl(list,list->start[level],level);
}

struct snode *create_skiplist_snode( char *name, char *ip, struct snode *next, struct snode *down){
    struct snode *node = (struct snode *)malloc(sizeof(struct snode));

    if(name != NULL)
        node->host_name = stringcopy(name);
    else node->host_name = NULL;

    if(ip != NULL)
        node->host_ip = stringcopy(ip);
    else node->host_ip = NULL;

    node->next = next;
    node->downlvl = down;
    return node;
}

struct skiplist *create_skiplist(int n){
    int i;
    struct skiplist *list = (struct skiplist *)malloc(sizeof(struct skiplist));
    list->size = 0;
    list->nlevel = SKIPLIST_MAX_LEVEL(n);

    struct snode *end = NULL;
    end = create_skiplist_snode(SKIPLIST_MAX_NAME,NULL,NULL,NULL);

    list->start = (struct snode **)malloc(sizeof(struct snode *)*list->nlevel);
    for(i = 0 ; i < list->nlevel ; i++){
        if(i == 0) list->start[i] = create_skiplist_snode(SKIPLIST_MIN_NAME,NULL,end,NULL);
        else list->start[i] = create_skiplist_snode(SKIPLIST_MIN_NAME,NULL,end,list->start[i-1]);
    }

    return list;
}

int letsflipacoin(){
    return rand() % 2;
}

int randlevel(int n){
    int level = 0;

    while(letsflipacoin()) level += 1;

    return level;
}

void insert_skiplist(struct snode *snode, char *name, char *ip, int level, int randlv, struct snode *prev){
    if(level == 0 && strcmp(name,snode->next->host_name)<0){
        struct snode *newnode = create_skiplist_snode(name,ip,snode->next,NULL);
        if(prev != NULL)prev->downlvl = newnode;
        snode->next = newnode;
        return;
    }

    if(strcmp(name,snode->next->host_name)<0){
        if(randlv >= level){
            struct snode *newnode = create_skiplist_snode(name,ip,snode->next,NULL);
            if(prev != NULL) prev->downlvl = newnode;
            snode->next = newnode;
            prev = newnode;
        }
        return insert_skiplist(snode->downlvl,name,ip,level-1,randlv,prev);
    }

    else
        return insert_skiplist(snode->next,name,ip,level,randlv,prev);
}

void search_skiplist(struct snode *node, char *name){
    if(node == NULL){
        printf("-1\n");
        return;
    }
    if(strcmp(node->next->host_name,name)==0){
        printf("%s\n",node->next->host_ip);
        return;
    }

    if(strcmp(name,node->next->host_name)<0)
        return search_skiplist(node->downlvl,name);
    else return search_skiplist(node->next,name);
}

void delete_skiplist(struct snode *node, char *name){
    if(node == NULL)
        return;

    if(strcmp(node->next->host_name,name)==0){
        struct snode *next = node->next->next;
        free(node->next->host_ip);
        free(node->next->host_name);
        free(node->next);
        node->next = next;
        return delete_skiplist(node->downlvl,name);
    }

    if(strcmp(name,node->next->host_name)<0)
        return delete_skiplist(node->downlvl,name);
    else return delete_skiplist(node->next,name);
}
