
/*********************************************************************
 * (C) Copyright 2000 Albert Ludwigs University Freiburg
 *     Institute of Computer Science
 *
 * All rights reserved. Use of this software is permitted for 
 * non-commercial research purposes, and it may be copied only 
 * for that use.  All copies must include this copyright message.
 * This software is made available AS IS, and neither the authors
 * nor the  Albert Ludwigs University Freiburg make any warranty
 * about the software or its performance. 
 *********************************************************************/









/*********************************************************************
 * File: memory.c
 * Description: Creation and Deletion functions for all data structures.
 *
 * Author: Joerg Hoffmann
 *
 *********************************************************************/ 









#include "ff.h"
#include "memory.h"
#include "lpg.h"
#include "parse.h"







/**********************
 * CREATION FUNCTIONS *
 **********************/











/* parsing
 */









char *new_Token( int len )

{

  char *tok = ( char * ) calloc( len, sizeof( char ) );
  CHECK_PTR(tok);

  return tok;

}



TokenList *new_TokenList( void )

{

  TokenList *result = ( TokenList * ) calloc( 1, sizeof( TokenList ) );
  CHECK_PTR(result);

  result->item = NULL; 
  result->next = NULL;

  return result;

}



FactList *new_FactList( void )

{

  FactList *result = ( FactList * ) calloc( 1, sizeof( FactList ) );
  CHECK_PTR(result);

  result->item = NULL; 
  result->next = NULL;

  return result;

}



TypedList *new_TypedList( void )

{

  TypedList *result = ( TypedList * ) calloc( 1, sizeof( TypedList ) );
  CHECK_PTR(result);

  result->next = NULL;
  result->name = NULL; 
  result->type = NULL;
  result->n = -1;

  return result;

}



TypedListList *new_TypedListList( void )

{

  TypedListList *result = ( TypedListList * ) calloc( 1, sizeof( TypedListList ) );
  CHECK_PTR(result);

  result->next = NULL;
  result->predicate = NULL; 
  result->args = NULL;

  return result;

}



PlNode *new_PlNode( Connective c )

{

  PlNode *result = ( PlNode * ) calloc( 1, sizeof( PlNode ) );
  CHECK_PTR(result);

  result->connective = c;
  result->atom = NULL;
  result->sons = NULL;
  result->next = NULL;
  result->is_start_end_ovr = IS_AT_START;
  
  return result;

}




PlNode *copy_PlNode(PlNode *p)
{
  PlNode *tmp;
  
  if (p == NULL)
    return NULL;

  tmp = new_PlNode(p->connective);
  tmp->is_start_end_ovr = p->is_start_end_ovr;
  tmp->value = p->value;
  tmp->atom = copy_TokenList(p->atom);
  tmp->parse_vars = copy_TypedList(p->parse_vars);
  
  tmp->next = copy_PlNode(p->next);
  tmp->sons = copy_PlNode(p->sons);
  

  return tmp;
}



PlOperator *new_PlOperator( char *name )

{

  PlOperator *result = ( PlOperator * ) calloc( 1, sizeof( PlOperator ) );
  CHECK_PTR(result);

  if ( name ) {
    result->name = new_Token(strlen(name)+1);
    CHECK_PTR(result->name);
    strcpy(result->name, name);
  } else {
    result->name = NULL;
  }

  result->params = NULL;
  result->preconds = NULL;
  result->effects = NULL;
  result->number_of_real_params = 0;
  result->next = NULL;
  
  /* For timed facts  */
  result->ops_type = NORMAL_ACT;
  /* end */

  result->to_delete = FALSE;

  return result;

}



PlOperator *new_axiom_op_list( void )

{

  static int count;
  char *name;
  PlOperator *ret;

  /* WARNING: count should not exceed 999 
   */
  count++;
  if ( count == 10000 ) {
    printf("\ntoo many axioms! look into memory.c, line 157\n\n");
    exit( 1 );
  }
  name = new_Token(strlen(HIDDEN_STR)+strlen(AXIOM_STR)+4+1);
  sprintf(name, "%s%s%4d", HIDDEN_STR, AXIOM_STR, count);

  ret = new_PlOperator(name);
  free(name);

  return ret;

}




State *new_State(int max_facts)
{
  State *result = NULL;

  result = (State *)calloc(1, sizeof(State));
  CHECK_PTR(result);
 
  result->F = (int *)calloc(max_facts, sizeof(int));
 
  return result;
}







/* instantiation
 */






FactList *copy_FactList(FactList *source)
{
  FactList *tmp;

  if (!source)
    return NULL;

  tmp = new_FactList();

  tmp->item = copy_TokenList(source->item);
  tmp->next = copy_FactList(source->next);

  return tmp;
}




Fact *new_Fact( void )

{

  Fact * result;
  result= ( Fact * ) calloc( 1, sizeof( Fact ) );
  CHECK_PTR(result);

  result->added_implicit = FALSE;
 
  
  return result;

}



Facts *new_Facts( void )

{

  Facts *result;
  result = ( Facts * ) calloc( 1, sizeof( Facts ) );
  CHECK_PTR(result);

  result->fact = new_Fact();

  result->next = NULL;

  return result;

}



WffNode *new_WffNode( Connective c )

{

  WffNode *result;
  result  = ( WffNode * ) calloc( 1, sizeof( WffNode ) );
  CHECK_PTR(result);

  result->connective = c;

  result->var = -1;
  result->var_type = -1;
  result->var_name = NULL;

  result->sons = NULL;
  result->next = NULL;
  result->prev = NULL;

  result->fact = NULL;
  result->NOT_p = -1;

  result->son = NULL;

  result->visited = FALSE;

  result->numeric = NULL;
  result->instantiated_vars = NULL;

  return result;

}



Literal *new_Literal( void ) 

{

  Literal *result;
  result = ( Literal * ) calloc( 1, sizeof( Literal ) );
  CHECK_PTR(result);

  result->next = NULL;
  result->prev = NULL;

  result->is_start_end_ovr = IS_AT_START;

  return result; 

}



Effect *new_Effect( void )

{

  Effect *result;
  result  = ( Effect * ) calloc( 1, sizeof( Effect ) );
  CHECK_PTR(result);

  result->num_vars = 0;

  result->conditions = NULL;

  result->effects = NULL;

  result->next = NULL;
  result->prev = NULL;

  return result;

}



Operator *new_Operator( char *name, int norp )

{

  int i;

  Operator *result;
  result = ( Operator * ) calloc( 1, sizeof( Operator ) );
  CHECK_PTR(result);

  if ( name ) {
    result->name = new_Token( strlen( name ) + 1 );
    CHECK_PTR( result->name );
    strcpy( result->name, name );
  } else {
    result->name = NULL;
  }

  result->num_vars = 0;
  result->number_of_real_params = norp;

  for ( i = 0; i < MAX_VARS; i++ ) {
    result->removed[i] = FALSE;
  }

  result->preconds = NULL;

  result->effects = NULL;

  result->hard = TRUE;

  result->ops_type = NORMAL_ACT;

  return result;

}



NormEffect *new_NormEffect1( Effect *e )

{

  int i;

  NormEffect *result;
  result = ( NormEffect * ) calloc( 1, sizeof( NormEffect ) );
  CHECK_PTR(result);

  result->num_vars = e->num_vars;
  for ( i = 0; i < e->num_vars; i++ ) {
    result->var_types[i] = e->var_types[i];
    result->inst_table[i] = -1;
  }

  result->conditions = NULL;
  result->num_conditions = 0;

  result->adds = NULL;
  result->num_adds = 0;
  result->dels = NULL;
  result->num_dels = 0;

  result->next = NULL;
  result->prev = NULL;

  return result;

}



NormEffect *new_NormEffect2( NormEffect *e )

{

  int i, j, a;

  NormEffect *result;
  result = ( NormEffect * ) calloc( 1, sizeof( NormEffect ) );
  CHECK_PTR(result);

  result->num_vars = 0;

  result->conditions = ( Fact * ) calloc( e->num_conditions, sizeof( Fact ) );
  result->num_conditions = e->num_conditions;
  for ( i = 0; i < e->num_conditions; i++ ) {
    result->conditions[i].predicate = e->conditions[i].predicate;
    a = ( e->conditions[i].predicate < 0 ) ? 2 : garity[e->conditions[i].predicate];
    for ( j = 0; j < a; j++ ) {
      result->conditions[i].args[j] = e->conditions[i].args[j];
    }
  }

  result->adds = ( Fact * ) calloc( e->num_adds, sizeof( Fact ) );
  result->num_adds = e->num_adds;
  for ( i = 0; i < e->num_adds; i++ ) {
    result->adds[i].predicate = e->adds[i].predicate;
    for ( j = 0; j < garity[e->adds[i].predicate]; j++ ) {
      result->adds[i].args[j] = e->adds[i].args[j];
    }
  }
  result->dels = ( Fact * ) calloc( e->num_dels, sizeof( Fact ) );
  result->num_dels = e->num_dels;
  for ( i = 0; i < e->num_dels; i++ ) {
    result->dels[i].predicate = e->dels[i].predicate;
    for ( j = 0; j < garity[e->dels[i].predicate]; j++ ) {
      result->dels[i].args[j] = e->dels[i].args[j];
    }
  }

  result->next = NULL;
  result->prev = NULL;

  return result;

}



NormOperator *new_NormOperator( Operator *op )

{

  int i;

  NormOperator *result;
  result = ( NormOperator * ) calloc( 1, sizeof( NormOperator ) );
  CHECK_PTR(result);

  result->l_operator = op;

  result->num_vars = op->num_vars;
  for ( i = 0; i < op->num_vars; i++ ) {
    result->var_types[i] = op->var_types[i];
    result->inst_table[i] = -1;
  }
  result->num_removed_vars = 0;

  result->preconds = NULL;
  result->num_preconds = 0;

  result->effects = NULL;

  result->inequals_constr = NULL;

  result->suspected = FALSE;

  result->numeric = NULL;
  result->instantiated_vars = NULL;

  return result;

}




EasyTemplate *new_EasyTemplate( NormOperator *op )

{

  EasyTemplate *result;
  result = ( EasyTemplate * ) calloc( 1, sizeof( EasyTemplate ) );
  CHECK_PTR(result);

  result->op = op;

  result->prev = NULL;
  result->next = NULL;

  result->suspected = op->suspected;
  
  return result;

}



MixedOperator *new_MixedOperator( Operator *op )

{

  MixedOperator *result;
  result  = ( MixedOperator * ) calloc( 1, sizeof( MixedOperator ) );
  CHECK_PTR(result);

  result->l_operator = op;

  result->preconds = NULL;
  result->num_preconds = 0;

  result->effects = NULL;
  
  result->numeric = NULL;
  result->instantiated_vars = NULL;

  return result;

}



PseudoActionEffect *new_PseudoActionEffect( void )

{

  PseudoActionEffect *result;
  result = ( PseudoActionEffect * ) calloc( 1, sizeof( PseudoActionEffect ) );
  CHECK_PTR(result);

  result->conditions = NULL;
  result->num_conditions = 0;

  result->adds = NULL;
  result->num_adds = 0;
  result->dels = NULL;
  result->num_dels = 0;

  result->next = NULL;

  return result;

}



PseudoAction *new_PseudoAction( MixedOperator *op )

{

  int i;

  PseudoAction *result = ( PseudoAction * ) calloc( 1, sizeof( PseudoAction ) );
  CHECK_PTR(result);

  result->l_operator = op->l_operator;
  for ( i = 0; i < op->l_operator->num_vars; i++ ) {
    result->inst_table[i] = op->inst_table[i];
  }

  result->preconds = op->preconds;
  result->num_preconds = op->num_preconds;

  result->effects = NULL;
  result->num_effects = 0;

  result->numeric = NULL;
  result->instantiated_vars = NULL;

  return result;

}



Action *new_Action( void )

{

  Action *result;

  result = ( Action * ) calloc( 1, sizeof( Action ) );
  CHECK_PTR(result);

  result->norm_operator = NULL;
  result->pseudo_action = NULL;

  result->next = NULL;

  result->suspected = FALSE;

  return result;

}



EhcNode *new_EhcNode( void )

{

  EhcNode *result;

  result = ( EhcNode * ) calloc( 1, sizeof( EhcNode ) );
  CHECK_PTR(result);

  result->father = NULL;
  result->next = NULL;

  result->new_goal = -1;

  result->S.F = (int *)calloc(max_state_facts, sizeof(int));

  return result;

}



EhcHashEntry *new_EhcHashEntry( void )

{

  EhcHashEntry *result = ( EhcHashEntry * ) calloc( 1, sizeof( EhcHashEntry ) );
  CHECK_PTR(result);

  result->ehc_node = NULL;

  result->next = NULL;

  return result;

}



PlanHashEntry *new_PlanHashEntry( void )

{

  PlanHashEntry *result;

  result= ( PlanHashEntry * ) calloc( 1, sizeof( PlanHashEntry ) );
  CHECK_PTR(result);

  result->next_step = NULL;

  result->next = NULL;

  result->S.F = (int *)calloc(max_state_facts, sizeof(int));

  return result;

}



BfsNode *new_BfsNode( void )

{

  BfsNode *result = ( BfsNode * ) calloc( 1, sizeof( BfsNode ) );
  CHECK_PTR(result);

  result->father = NULL;
  result->next = NULL;
  result->prev = NULL;

  result->S.F = (int *)calloc(max_state_facts, sizeof(int));

  return result;

}



BfsHashEntry *new_BfsHashEntry( void )

{

  BfsHashEntry *result;

  result  = ( BfsHashEntry * ) calloc( 1, sizeof( BfsHashEntry ) );
  CHECK_PTR(result);

  result->bfs_node = NULL;

  result->next = NULL;

  return result;

}




VarList *new_VarList(Token name, int num)
{
  VarList *result;

  result = (VarList *)calloc(1, sizeof(VarList));
  CHECK_PTR(result);

  result->name = copy_Token(name);
  result->n = num;

  result ->next = NULL;

  return result;
}


VarList *copy_VarList(VarList *v)
{
  VarList *result;

  if (!v)
    return NULL;

  result = new_VarList(v->name, v->n);
  result->next = copy_VarList(v->next);

  return result;

}


/**********************
 * DELETION FUNCTIONS *
 **********************/












void free_TokenList( TokenList *source )

{

  if ( source ) {
    free_TokenList( source->next );
    if ( source->item ) {
      free( source->item );
    }
    free( source );
  }

}



void free_FactList( FactList *source )

{

  if ( source ) {
    free_FactList( source->next );
    free_TokenList( source->item );
    free( source );
  }

}



void free_PlNode( PlNode *node )

{
  
  if ( node ) {
    free_TypedList( node -> parse_vars );
    free_PlNode( node->sons );
    free_PlNode( node->next );
    free_TokenList( node->atom );
    free( node );
  }

}



void free_PlOperator( PlOperator *o )

{

  if ( o ) {
    free_PlOperator( o->next );

    if ( o->name ) {
      free( o->name );
    }
    free_TypedList(o -> parse_params );
    free_FactList( o->params );
    free_PlNode( o->preconds );
    free_PlNode( o->effects );

    free( o );
  }

}



void free_Operator( Operator *o )

{

  if ( o ) {

    if ( o->name ) {
      free( o->name );
    }

    free( o );
  } 

}



void free_WffNode( WffNode *w )

{

  if ( w ) {
    free_WffNode( w->son );
    free_WffNode( w->sons );
    free_WffNode( w->next );
    if ( w->var_name ) {
      free( w->var_name );
    }
    if ( w->fact ) {
      free( w->fact );
    }
    free( w );
    w = NULL;
  }

}



void free_NormEffect( NormEffect *e )

{

  if ( e ) {
    free_NormEffect( e->next );

    if ( e->conditions ) {
      free( e->conditions );
    }
    if ( e->adds ) {
      free( e->adds );
    }
    if ( e->dels ) {
      free( e->dels );
    }

    free( e );
  }

}



void free_partial_Effect( Effect *e )

{

  if ( e ) {
    free_partial_Effect( e->next );

    free_WffNode( e->conditions );

    free( e );
  }

}



void free_NormOperator( NormOperator *o )

{

  if ( o ) {

    if ( o->preconds ) {
      free( o->preconds );
    }

    free_NormEffect( o->effects );

    free( o );
  }

}



void free_single_NormEffect( NormEffect *e )

{

  if ( e ) {
    if ( e->conditions ) {
      free( e->conditions );
    }
    if ( e->adds ) {
      free( e->adds );
    }
    if ( e->dels ) {
      free( e->dels );
    }

    free( e );
  }

}



void free_single_EasyTemplate( EasyTemplate *t )

{

  if ( t ) {
    free( t );
  }

}



void free_TypedList( TypedList *t )

{

  if ( t ) {
    if ( t->name ) {
      free( t->name );
      t->name = NULL;
    }
    if ( t->type ) {
      free_TokenList( t->type );
      t->type = NULL;
    }
    free_TypedList( t->next );

    free( t );
  }

}



void free_TypedListList( TypedListList *t )

{

  if ( t ) {
    if ( t->predicate ) {
      free( t->predicate );
      t->predicate = NULL;
    }
    if ( t->args ) {
      free_TypedList( t->args );
      t->args = NULL;
    }
    free_TypedListList( t->next );

    free( t );
  }

}

IntList *free_intlist (IntList * ilist)
{
  IntList *nextil;
 
  while (ilist)
    {
      nextil = ilist->next;
      free (ilist);
      ilist = nextil;
    }
  return NULL;
}


void free_Facts( Facts *f ) {
  if (f) {
    if (f -> fact)
      free(f -> fact);
    free_Facts(f -> next);
    free(f);  
  }
}



IntList *new_IntList (void)
{

  IntList *result = (IntList *) calloc (1, sizeof (IntList));
  CHECK_PTR (result);

  memset(result, 0, sizeof(IntList));

  return result;

}



IntList *get_IntList( void ) 
{
  IntList *tmp;

  if (old_list) 
    {
      tmp = old_list;
      old_list = tmp->next;
      tmp->next = NULL;
    }
  else
    tmp = new_IntList();
  
  return tmp;

}


void trash_IntList(IntList *t)
{
  IntList *tmp = NULL;

  if (t == NULL)
    return;

  for (tmp = t; tmp && tmp->next; tmp = tmp->next);
  
  if (tmp)
    {
      tmp->next = old_list;
      old_list = t;
      t = NULL;
    }

}
