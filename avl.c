#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no
{
    int chave;
    struct no *esq, *dir;
    int bal;
} No;

////////////////////////////////////////////////////////
void iniciarNo(No **pt, int x)
{

    No *novo = (No *)malloc(sizeof(No));

    // Se foi possível alocar.
    if (novo)
    {
        novo->chave = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->bal = 0;

        (*pt) = novo;
    }
    else
    {
        printf("Ocorreu algum erro ao alocar o Nó.");
    }
}

void Caso1I(No **pt, int *h)
{
    No *ptu;
    ptu = (*pt)->esq;

    if (ptu->bal == -1)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        *pt = ptu;
        (*pt)->dir->bal = 0;
    }
    else
    {
        No *ptv;
        ptv = ptu->dir;

        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;

        if (ptv->bal == 1)
        {
            (*pt)->bal = 0;

            if (ptu->esq == NULL && ptu->dir == NULL)
            {
                ptu->bal = 0;
            }
            else
            {
                ptu->bal = -1;
            }
        }
        else
        {

            if ((*pt)->esq == NULL && (*pt)->dir == NULL)
            {
                (*pt)->bal = 0;
            }
            else
            {
                (*pt)->bal = 1;
            }

            ptu->bal = 0;
        }

        *pt = ptv;
    }

    (*pt)->bal = 0;
    (*h) = 0;
}

void Caso2I(No **pt, int *h)
{
    No *ptu;
    ptu = (*pt)->dir;

    if (ptu->bal == 1)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        *pt = ptu;
        (*pt)->esq->bal = 0;
    }
    else
    {
        No *ptv;
        ptv = ptu->esq;

        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;

        if (ptv->bal == -1)
        {
            (*pt)->bal = 0;

            if (ptu->esq == NULL && ptu->dir == NULL)
            {
                ptu->bal = 0;
            }
            else
            {
                ptu->bal = 1;
            }
        }
        else
        {

            if ((*pt)->esq == NULL && (*pt)->dir == NULL)
            {
                (*pt)->bal = 0;
            }
            else
            {
                (*pt)->bal = -1;
            }

            ptu->bal = 0;
        }

        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    (*h) = 0;
}

void InserirAVL(int x, No **pt, int *h)
{
    if (*pt == NULL)
    {
        iniciarNo(pt, x);
        (*h) = 1;
    }
    else
    {
        if (x == (*pt)->chave)
        {
            // printf("elem. encontrado");
        }
        else if (x < (*pt)->chave)
        {
            InserirAVL(x, &(*pt)->esq, h);
            if ((*h) == 1)
            {
                if ((*pt)->bal == 1)
                {
                    (*pt)->bal = 0;
                    (*h) = 0;
                }
                else if ((*pt)->bal == 0)
                {
                    (*pt)->bal = -1;
                }
                else if ((*pt)->bal == -1)
                {
                    Caso1I(pt, h);
                }
            }
        }
        else
        {
            InserirAVL(x, &(*pt)->dir, h);
            if ((*h) == 1)
            {
                if ((*pt)->bal == -1)
                {
                    (*pt)->bal = 0;
                    (*h) = 0;
                }
                else if ((*pt)->bal == 0)
                {
                    (*pt)->bal = 1;
                }
                else if ((*pt)->bal == 1)
                {
                    Caso2I(pt, h);
                }
            }
        }
    }
}
////////////////////////////////////////////////////////
void Caso1R(No **pt, int *h)
{
    No *ptu;
    ptu = (*pt)->esq;

    if (ptu->bal <= 0)
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;

        if (ptu->bal == -1)
        {
            ptu->bal = (*pt)->dir->bal = 0;
            (*h) = 1;
        }
        else
        {
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            (*h) = 0;
        }
    }
    else
    {
        No *ptv;
        ptv = ptu->dir;

        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;

        if (ptv->bal == -1)
        {
            ptu->bal = 0;
            (*pt)->dir->bal = 1;
        }
        else if (ptv->bal == 0)
        {
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
        }
        else if (ptv->bal == 1)
        {
            ptu->bal = -1;
            (*pt)->dir->bal = 0;
        }

        (*pt)->bal = 0;
        (*h) = 1;
    }
}

void Caso2R(No **pt, int *h)
{
    No *ptu;
    ptu = (*pt)->dir;

    if (ptu->bal >= 0)
    {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;

        if (ptu->bal == 1)
        {
            ptu->bal = 0;
            (*pt)->esq->bal = 0;
            (*h) = 1;
        }
        else
        {
            ptu->bal = -1;
            (*pt)->esq->bal = 1;
            (*h) = 0;
        }
    }
    else
    {
        No *ptv;
        ptv = ptu->esq;

        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;

        if (ptv->bal == 1)
        {
            ptu->bal = 0;
            (*pt)->esq->bal = -1;
        }
        else if (ptv->bal == 0)
        {
            ptu->bal = 0;
            (*pt)->esq->bal = 0;
        }
        else if (ptv->bal == -1)
        {
            ptu->bal = 1;
            (*pt)->esq->bal = 0;
        }

        (*pt)->bal = 0;
        (*h) = 1;
    }
}

void balancear(No **pt, char R, int *h)
{
    if ((*h) == 1)
    {
        if (R == 'D')
        {
            if ((*pt)->bal == 1)
            {
                (*pt)->bal = 0;
            }
            else if ((*pt)->bal == 0)
            {
                (*pt)->bal = -1;
                (*h) = 0;
            }
            else if ((*pt)->bal == -1)
            {
                Caso1R(&(*pt), h);
            }
        }
        else
        {
            if ((*pt)->bal == -1)
            {
                (*pt)->bal = 0;
            }
            else if ((*pt)->bal == 0)
            {
                (*pt)->bal = 1;
                (*h) = 0;
            }
            else if ((*pt)->bal == 1)
            {
                Caso2R(&(*pt), h);
            }
        }
    }
}

void trocar(No **no1, No **no2)
{
    int aux = (*no1)->chave;
    (*no1)->chave = (*no2)->chave;
    (*no2)->chave = aux;
}

void RemoverAVL(int x, No **pt, int *h)
{
    if ((*pt) == NULL)
    {
        printf("elem. não existe.\n");
        (*h) = 0;
    }
    else
    {
        if (x < (*pt)->chave)
        {
            RemoverAVL(x, &(*pt)->esq, h);
            balancear(&(*pt), 'E', h);
        }
        else
        {
            if (x > (*pt)->chave)
            {
                RemoverAVL(x, &(*pt)->dir, h);
                balancear(&(*pt), 'D', h);
            }
            else
            {
                No *aux;
                aux = (*pt);

                if ((*pt)->esq == NULL)
                {
                    (*pt) = (*pt)->dir;
                    (*h) = 1;
                    free(aux);
                }
                else
                {
                    if ((*pt)->dir == NULL)
                    {
                        (*pt) = (*pt)->esq;
                        (*h) = 1;
                        free(aux);
                    }
                    else
                    {
                        No *s;
                        s = (*pt)->dir;

                        if (s->esq == NULL)
                        {
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            (*h) = 1;
                            free(aux);
                        }
                        else
                        {
                            No *PaiS;
                            PaiS = s;

                            while (s->esq != NULL)
                            {
                                PaiS = s;
                                s = s->esq;
                            }

                            trocar(pt, &(PaiS)->esq);
                            RemoverAVL(x, &(*pt)->dir, h);
                        }
                        balancear(pt, 'D', h);
                    }
                }
            }
        }
    }
}
////////////////////////////////////////////////////////
int alturaNo(No *pt)
{
    if (pt == NULL)
    {
        return 0;
    }
    else
    {

        int alturaEsq = alturaNo(pt->esq);
        int alturaDir = alturaNo(pt->dir);

        if (alturaEsq >= alturaDir)
        {
            return alturaEsq + 1;
        }
        else
        {
            return alturaDir + 1;
        }
    }
}

int balNo(No *pt)
{
    return (alturaNo(pt->dir) - alturaNo(pt->esq));
}

int ehAvl(No *pt)
{
    int ehAVL;

    if (pt == NULL)
    {
        return 1;
    }
    else
    {
        int esqEhAVL = ehAvl(pt->esq);
        int dirEhAVL = ehAvl(pt->dir);

        if (esqEhAVL == 0 || dirEhAVL == 0)
        {
            return 0;
        }

        int balDoNo = balNo(pt);

        if (balDoNo >= -1 && balDoNo <= 1)
        {
            ehAVL = 1;
        }
        else
        {
            ehAVL = 0;
        }

        if (balDoNo != pt->bal)
        {
            printf("O bal do nó %d está errado. O correto seria %d, ao invés de %d\n", pt->chave, balDoNo, pt->bal);
            return 0;
        }

        return ehAVL;
    }
}

int qtdNosAVL(No *pt)
{
    if (pt == NULL)
    {
        return 0;
    }
    return qtdNosAVL(pt->esq) + qtdNosAVL(pt->dir) + 1;
}

void liberarAVL(No *pt)
{
    if (pt != NULL)
    {
        liberarAVL(pt->esq);
        liberarAVL(pt->dir);

        free(pt);
    }
}

int chaveExiste(No *pt, int x)
{
    while (pt != NULL)
    {
        if (x > pt->chave)
        {
            pt = pt->dir;
        }
        else if (x < pt->chave)
        {
            pt = pt->esq;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}
////////////////////////////////////////////////////////

void imprimirNo(No **pt, int nivel)
{
    int i;
    if ((*pt))
    {
        imprimirNo(&(*pt)->dir, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
        {
            printf("\t");
        }

        printf("%d: %d", (*pt)->chave, (*pt)->bal);
        imprimirNo(&(*pt)->esq, nivel + 1);
    }
}

int main()
{
    int qtdAVL_ParaCriar = 1000;   // Quantas AVLs devem ser criadas.
    int qtdNosParaCadaAvl = 10000; // Quantos Nós cada AVL deve possuir.
    int qtdNosParaRemover = 1000;  // Quantos Nós para remover em cada AVL.

    for (int i = 0; i < qtdAVL_ParaCriar; i++)
    {
        No *pt = NULL;
        int h;

        int numGerado = 0;

        int qtdNosDaAVL;
        ////////////////////////////////////////////////////////
        for (int j = 0; j < qtdNosParaCadaAvl; j++)
        {
            h = 0;
            numGerado = rand() % 100000;
            InserirAVL(numGerado, &pt, &h);
        }

        while (qtdNosAVL(pt) < qtdNosParaCadaAvl)
        {
            h = 0;
            numGerado = rand() % 100000;
            InserirAVL(numGerado, &pt, &h);
        }

        printf("\n\n---------------------- AVL #%d ----------------------\n", i + 1);

        qtdNosDaAVL = qtdNosAVL(pt);
        if (qtdNosDaAVL == qtdNosParaCadaAvl)
        {
            printf("A AVL possui %d Nós.\n", qtdNosParaCadaAvl);
        }
        else
        {
            printf("A AVL não possui %d Nós. Ela possui %d Nós.\n", qtdNosParaCadaAvl, qtdNosDaAVL);
        }

        if (ehAvl(pt) == 1)
        {
            printf("De fato, é AVL.\n");
        }
        else
        {
            printf("Não é AVL.\n");
        }
        ////////////////////////////////////////////////////////
        for (int l = 0; l < qtdNosParaRemover; l++)
        {
            RemoverAVL(pt->chave, &pt, &h);
        }

        qtdNosDaAVL = qtdNosAVL(pt);
        if (qtdNosDaAVL == (qtdNosParaCadaAvl - qtdNosParaRemover))
        {
            printf("Após %d remoções, a AVL possui %d Nós.\n", qtdNosParaRemover, (qtdNosParaCadaAvl - qtdNosParaRemover));
        }
        else
        {
            printf("Após %d remoções, a AVL não possui %d Nós. Ela possui %d Nós.\n", qtdNosParaRemover, (qtdNosParaCadaAvl - qtdNosParaRemover), qtdNosDaAVL);
        }

        if (ehAvl(pt) == 1)
        {
            printf("Após as remoções, ainda é AVL.\n");
        }
        else
        {
            printf("Após as remoções, não é mais AVL.\n");
        }

        printf("----------------------------------------------------\n\n");
        ////////////////////////////////////////////////////////
        liberarAVL(pt);
    }

    return 0;
}