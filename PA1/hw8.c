#ifndef __PROGTEST__
#endif /* __PROGTEST__ */

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{
    
    TEMPLOYEE *link = (TEMPLOYEE*) malloc(sizeof(*link));
    char *nName =(char*) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(nName,name);
    
    link -> m_Bak = NULL;
    link -> m_Name = nName;
    link -> m_Next = next;
    return link;
    
}
TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src )
{
    TEMPLOYEE *original, *toCopy, *cnode;
    
    if (!src) return NULL;
    original = src; toCopy = NULL; cnode = NULL;
    for ( ; original; original = original->m_Next->m_Next) {
        cnode = newEmployee(original->m_Name, original->m_Next);
        cnode->m_Bak = original->m_Bak;
        if (original == src)
            toCopy = cnode;
        original->m_Next = cnode;
    }
    
    for (original = src; original && original->m_Next;
         original = original->m_Next->m_Next )
        if (original->m_Bak)
            original->m_Next->m_Bak = original->m_Bak->m_Next;
        else
            original->m_Next->m_Bak = NULL;
    
    original = src; cnode = toCopy;
    for (;cnode && cnode->m_Next; original = original->m_Next, cnode = cnode->m_Next) {
        original->m_Next = original->m_Next->m_Next;
        cnode->m_Next = cnode->m_Next->m_Next;
    }
    original->m_Next = NULL;
    return toCopy;
}
void               freeList     ( TEMPLOYEE       * src )
{
    while (src != NULL)
    {
        TEMPLOYEE *toDel = src;
        src = src->m_Next;
        free(toDel->m_Name);
        free(toDel);
    }

}

#ifndef __PROGTEST__
#endif /* __PROGTEST__ */