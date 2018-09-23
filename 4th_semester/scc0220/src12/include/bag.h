#ifndef _BAG_H_
#define _BAG_H_

typedef struct bag t_bag;
struct bag{
    int nitens, *itens;
};

void destroybag(t_bag *);

int getminofthebag(t_bag *);
int getmaxofthebag(t_bag *);

boolean existinbag(int , t_bag *);

void putonbag(int , t_bag *);
int getfromstartbag(int , t_bag *);
int getfromendbag(int , t_bag *);

t_bag *createbag();

#endif