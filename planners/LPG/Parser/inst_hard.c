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
 * File: inst_hard.c
 * Description: functions for multiplying hard operators.
 *
 *
 * Author: Joerg Hoffmann 2000
 *
 *********************************************************************/ 








#include <math.h>
#include "ff.h"

#include "output.h"
#include "memory.h"

#include "inst_pre.h"
#include "inst_hard.h" 

/*
 * DEA
 */
#include "lpg.h"
#include "inst_utils.h"

/*
 * END OF DEA
 */








/* used in multiplying routines
 */
int linst_table[MAX_VARS];

Fact *lor_precs = NULL;
int lnum_or_precs;

/*
int_pointer lini[MAX_PREDICATES];
*/

bit_table lini;


/*
 * DEA - University of Brescia
 */
Bool initialized = FALSE;


/**
 * Inizializzo una hash table di tutti i fatti instanziati. Inserisco quelli
 * appartenenti allo stato iniziale
 **
 * Initialize a hash table of instantiated facts with facts in the 
 * initial state
 **/

void init_instantiated_facts_table() {

  int i, j, max_arity = 0;
  unsigned long int max_size, size, adr;

  /**
   * Valuto la massima arity dei predicati
   **
   * Evaluate max predicates arity
   **/
  for (i = 0; i < gnum_predicates; i++)
    if (garity[i] > max_arity) 
      max_arity = garity[i];
  
  /**
   * Stimo il massimo numero di fatti instanziabili a partire da 
   * un predicato
   **
   * Evaluate max predicates size
   **/
  max_size = 1;
  for (i = 0; i < max_arity; i++)
    max_size *= gnum_constants;

  max_size = max_arity * max_size;


  /**
   * Inizializzo la hash table
   **
   * Init the hash table
   **/

  /**
   * Ogni riga può avere al massimo max_size elementi
   **
   * Each row can have max_size elements
   **/
  lini.max_row_size = max_size;

  /**
   * Inizializzo le costanti che caratterizzano questa hash table
   **
   * Init the constats used for handling the hash table 
   **/
  init_bit_table_const(max_size, &lini.n_bit, &lini.base, &lini.bit_row_size);
  

  /**
   * Alloco memoria per la tabella vera e propria
   **
   * Allocate space for the real table
   **/
  lini.bits = (int_pointer **)calloc(gnum_predicates, sizeof(int_pointer *));
  assert(lini.bits);
  

  /**
   * Per ogni predicato inserisco una riga nella tabella
   **
   * Insert a new row in the table for each predicate
   **/
  for ( i = 0; i < gnum_predicates; i++ ) {
    size = 1;
    for ( j = 0; j < garity[i]; j++ ) {
      size *= gnum_constants;
    }

    size = garity[i] * size;
    
    /**
     * Ogni riga è a sua volta una matrice (parzialmente allocata)
     * Inizializzo la riga corrente
     **
     * Each row is implemented as a matrix. Initialize it.
     **/
    init_bit_table_row(lini, i, size);

    for ( j = 0; j < gnum_initial_predicate[i]; j++ ) {
      adr = instantiated_fact_adress( &ginitial_predicate[i][j] );
      insert_bit_in_bit_table(lini, i, adr);
    }
  }

  initialized = TRUE;
}


/*
 * End of DEA
 */


void build_hard_action_templates( )

{

  int i;
  MixedOperator *o;

  if (!initialized)
    init_instantiated_facts_table();
  
  /* remove unused params; empty types are already recognised during
   * domain translation; have to be handled after (or while)
   * unaries encoding (if done), though.
   */
  cleanup_hard_domain( ghard_operators, &gnum_hard_operators );

  if ( gcmd_line.display_info == 115 ) {
    printf("\n\ncleaned up hard domain representation is:\n\n");
    for ( i = 0; i < gnum_hard_operators; i++ ) {
      print_Operator( ghard_operators[i] );
    }
  }

  /* create mixed op for each param combination
   */
  multiply_hard_op_parameters( ghard_operators, &gnum_hard_operators );

  if ( gcmd_line.display_info == 116 ) {
    printf("\n\nmixed hard domain representation is:\n\n");
    for ( o = ghard_mixed_operators; o; o = o->next ) {
      print_MixedOperator( o );
    }
  }


  /* create pseudo op for each mixed op
   */
  multiply_hard_effect_parameters( &ghard_templates, &gnum_hard_templates);
 
  if ( gcmd_line.display_info == 117 ) {
    printf("\n\npseudo hard domain representation is:\n\n");
    for ( i = 0; i < gnum_hard_templates; i++ ) {
      print_PseudoAction( ghard_templates[i] );
    }
  } 

}




Bool derived_hard_analisys = FALSE;

/*
 * DEA - University of Brescia
 */

/**
 * Costruisco i template per i predicati derivati
 **
 * Build templates for derived predicates 
 **/
void build_hard_derived_predicates_templates( )
{

  int i;

  derived_hard_analisys = TRUE;

  if (!initialized)
    init_instantiated_facts_table();

  /**
   * remove unused params; empty types are already recognised during
   * domain translation; have to be handled after (or while)
   * unaries encoding (if done), though.
   **/
  cleanup_hard_domain( ghard_derivedpred, &gnum_hard_derivedpred );

  if ( gcmd_line.display_info == 115 ) {
    printf("\n\nDerived predicates: cleaned up hard domain representation is:\n\n");
    for ( i = 0; i < gnum_hard_derivedpred; i++ ) {
      print_Operator( ghard_derivedpred[i] );
    }
  }

  /* create mixed op for each param combination
   */
  multiply_hard_op_parameters( ghard_derivedpred, &gnum_hard_derivedpred );

  /* create pseudo op for each mixed op
   */
  multiply_hard_effect_parameters( &ghard_dp_templates, &gnum_hard_dp_templates);

  if ( gcmd_line.display_info == 117 ) {
    printf("\n\nDerived predicates: pseudo hard domain representation is:\n\n");
    for ( i = 0; i < gnum_hard_dp_templates; i++ ) {
      print_PseudoAction( ghard_dp_templates[i] );
    }
  } 

  derived_hard_analisys = FALSE;
 
}








/****************
 * CLEANUP CODE *
 ****************/












void cleanup_hard_domain( Operator_pointer *ghard_op, int *gnum_hard_op )

{

  int i, j, k, par;
  Operator *o;
  Effect *e;

  /* so far, only unused parameters removal
   */

  for ( i = 0; i < (*gnum_hard_op); i++ ) {
    o = ghard_op[i];

    j = 0;
    while ( j < o->num_vars ) {
      if ( var_used_in_wff( ENCODE_VAR( j ), o->preconds ) ) {
	j++;
	continue;
      }

      for ( e = o->effects; e; e = e->next ) {
	if ( var_used_in_wff( ENCODE_VAR( j ), e->conditions ) ) {
	  break;
	}
	if ( var_used_in_literals( ENCODE_VAR( j ), e->effects ) ) {
	  break;
	}
      }
      if ( e ) {
	j++;
	continue;
      }

      o->removed[j] = TRUE;
      j++;
    }

    for ( e = o->effects; e; e = e->next ) {
      j = 0;
      while ( j < e->num_vars ) {
	par = o->num_vars + j;
	if ( var_used_in_wff( ENCODE_VAR( par ), e->conditions ) ) {
	  j++;
	  continue;
	}
	if ( var_used_in_literals( ENCODE_VAR( par ), e->effects ) ) {
	  j++;
	  continue;
	}

	if ( e->var_names[j] ) {
	  free( e->var_names[j] );
	}
	for ( k = j; k < e->num_vars - 1; k++ ) {
	  e->var_names[k] = e->var_names[k+1];
	  e->var_names[k] = e->var_names[k+1];
	}
	e->num_vars--;
	decrement_inferior_vars( par, e->conditions );
	decrement_inferior_vars_in_literals( par, e->effects );
      }
    }
  }

}



Bool var_used_in_literals( int code_var, Literal *ef )

{

  Literal *l;
  int i;
  
  for ( l = ef; l; l = l->next ) {
    for ( i = 0; i < garity[l->fact.predicate]; i++ ) {
      if ( l->fact.args[i] == code_var ) {
	return TRUE;
      }
    }
  }

  return FALSE;

}



void decrement_inferior_vars_in_literals( int var, Literal *ef )

{

  Literal *l;
  int i;
  
  for ( l = ef; l; l = l->next ) {
    for ( i = 0; i < garity[l->fact.predicate]; i++ ) {
      if ( l->fact.args[i] >= 0 ) {
	continue;
      }
      if ( DECODE_VAR( l->fact.args[i] ) > var ) {
	l->fact.args[i]++;
      }
    }
  }

}














/******************************
 * CODE THAT BUILDS MIXED OPS *
 ******************************/










Bool lused_const[MAX_CONSTANTS];









void multiply_hard_op_parameters( Operator_pointer *ghard_op, int *gnum_hard_op )

{

  int i;

  ghard_mixed_operators = NULL;

  for ( i = 0; i < gnum_constants; i++ ) {
    lused_const[i] = FALSE;
  }
  for ( i = 0; i < MAX_VARS; i++ ) {
    linst_table[i] = -1;
  }

  for ( i = 0; i < (*gnum_hard_op); i++ ) {
    create_hard_mixed_operators( ghard_op[i], 0 );
  }

}


Bool contains_ORs(WffNode *w) {

  WffNode *tmp;
  
  if (w == NULL)
    return FALSE;
  
  switch (w->connective) {
  case OR:
    return TRUE;
  case AND:
    for (tmp = w->sons; tmp; tmp = tmp->next)
      if (contains_ORs(tmp))
	return TRUE;
    break;
  case NOT:
    if (contains_ORs(w->son))
      return TRUE;
    break;
  case ATOM:
    return FALSE;
    break;
  default:
    break;
  }

  return FALSE;
}


void collect_hard_or_preconditions(WffNode *w, Bool first) {

  int m, j;
  WffNode *ww;
  Fact *tmp_ft;

  if (w == NULL)
    return;

  if (first) {

    if (!contains_ORs(w))
      return;

    m = count_all_facts(w);
    if (m > 0)
      lor_precs = ( Fact * ) calloc( m, sizeof( Fact ) );
    else
      lor_precs = NULL;

    lnum_or_precs = 0;
  }

  switch (w->connective) {
  case BIN_COMP:
    break;
  case OR:
  case AND:
    for (ww = w->sons; ww; ww = ww->next)
      collect_hard_or_preconditions(ww, FALSE);
    break;
  case ATOM:
    if (w->fact->predicate < 0)
      break;
    tmp_ft = &lor_precs[lnum_or_precs];
    lnum_or_precs++;
    tmp_ft->predicate = w->fact->predicate;
    tmp_ft->is_start_end_ovr = w->fact->is_start_end_ovr;
    for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
      tmp_ft->args[j] = w->fact->args[j];
    }
    break;
  case NOT:
#ifdef __MY_OUTPUT__
    if ((w->son->connective != ATOM) || 
	(w->son->fact->predicate >= 0))
      printf("Warning: NOT with ATOM son in collect_hard_or_preconditions()");
#endif
    break;
  default:
#ifdef __MY_OUTPUT__
    printf("Warning: unexpected node in collect_hard_or_preconditions()");
#endif
    break;
  }

}

void add_or_preconditions_to_mixed_op(MixedOperator *op) {

  int i, j;
  Fact *tmp;

  op->or_precs = lor_precs;
  op->num_or_precs = lnum_or_precs;
  
  for (i = 0; i < lnum_or_precs; i++) {
    tmp = &lor_precs[i];
    for (j = 0; j < garity[tmp->predicate]; j++) {
      if (tmp->args[j] < 0)
	tmp->args[j] = linst_table[DECODE_VAR(tmp->args[j])];
    }
  } 

}



void create_hard_mixed_operators( Operator *o, int curr_var )

{

  int t, i, m;
  WffNode *tmp1, *w, *ww;
  MixedOperator *tmp2;
  PlNode *pl;
  VarList *inst_var;

  if ( curr_var < o->num_vars ) {
    if ( o->removed[curr_var] ) {
      /* param doesn't matter -- select any appropriate type constant
       * at least one there; otherwise, op would not have been translated.
       */
      linst_table[curr_var] = gtype_consts[o->var_types[curr_var]][0];
      create_hard_mixed_operators( o, curr_var + 1 );
      linst_table[curr_var] = -1;
      return;
    }

    t = o->var_types[curr_var];
    for ( i = 0; i < gtype_size[t]; i++ ) {

      if (derived_hard_analisys && lused_const[gtype_consts[t][i]])
	break;

      linst_table[curr_var] = gtype_consts[t][i];
      lused_const[gtype_consts[t][i]] = TRUE;

      create_hard_mixed_operators( o, curr_var + 1 );

      linst_table[curr_var] = -1;
      lused_const[gtype_consts[t][i]] = FALSE;
    }
    return;
  }

  collect_hard_or_preconditions(o->preconds, TRUE);
  tmp1 = instantiate_wff( o->preconds );

  if ( tmp1->connective == FAL ) {
    free_WffNode( tmp1 );
    return;
  }

  dnf( &tmp1 );
  cleanup_wff( &tmp1 );

  if ( tmp1->connective == FAL ) {
    free_WffNode( tmp1 );
    return;
  }

  /* only debugging, REMOVE LATER
   */
  if ( is_dnf( tmp1 ) == -1 ) {
    printf("\n\nILLEGAL DNF %s AFTER INSTANTIATION\n\n", o->name);
    print_Wff( tmp1, 0 );
    exit( 1 );
  }

  switch ( tmp1->connective ) {
  case OR:
    for ( w = tmp1->sons; w; w = w->next ) {
      tmp2 = new_MixedOperator( o );
      add_or_preconditions_to_mixed_op(tmp2);
      for ( i = 0; i < o->num_vars; i++ ) {
	tmp2->inst_table[i] = linst_table[i];
      }
      if ( w->connective == AND ) {
	m = 0;
	for ( ww = w->sons; ww; ww = ww->next )
	  if (ww->connective != BIN_COMP) m++;
	tmp2->preconds = ( Fact * ) calloc( m, sizeof( Fact ) );
	tmp2->num_preconds = m;
	m = 0;
	for ( ww = w->sons; ww; ww = ww->next ) {

	  /*
	   * DEA - University of Brescia
	   */

	  /**
	   * Le precondizioni numeriche vengono inserite come PlNode.
	   * Saranno tradotte in seguito.
	   **
	   * Numeric preconditions are copied as PlNodes.
	   * They will be translated after.
	   **/
	  if (ww->connective == BIN_COMP)
	    {
	      if (!tmp2->numeric)
		tmp2->numeric = copy_PlNode(ww->numeric);
	      else
		{
		  for (pl = tmp2->numeric; pl && pl->next; pl = pl->next);
		  pl->next =  copy_PlNode(ww->numeric);
		}

	      if (!tmp2->instantiated_vars)
		tmp2->instantiated_vars = copy_VarList(ww->instantiated_vars);
	      else
		{
		  for (inst_var = tmp2->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
		  inst_var->next = copy_VarList(ww->instantiated_vars);
		}

	      continue;
	    }
	  /*
	   * End of DEA
	   */
	  tmp2->preconds[m].is_start_end_ovr = ww->is_start_end_ovr;
	  tmp2->preconds[m].predicate = ww->fact->predicate;
	  for ( i = 0; i < garity[ww->fact->predicate]; i++ ) {
	    tmp2->preconds[m].args[i] = ww->fact->args[i];
	  }
	  m++;
	}
      } else {

	/*
	 * DEA - University of Brescia
	 */
	
	/**
	 * Le precondizioni numeriche vengono inserite come PlNode.
	 * Saranno tradotte in seguito.
	 **
	 * Numeric preconditions are copied as PlNodes.
	 * They will be translated after.
	 **/
	
	if (w->connective == BIN_COMP)
	  {
	    if (!tmp2->numeric)
	      tmp2->numeric = copy_PlNode(w->numeric);
	    else
	      {
		for (pl = tmp2->numeric; pl && pl->next; pl = pl->next);
		pl->next =  copy_PlNode(w->numeric);
	      }

	    if (!tmp2->instantiated_vars)
	      tmp2->instantiated_vars = copy_VarList(w->instantiated_vars);
	    else
	      {
		for (inst_var = tmp2->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
		inst_var->next = copy_VarList(w->instantiated_vars);
	      }
	  }
	else

	  /*
	   * End of DEA
	   */

	  {
	    tmp2->preconds = ( Fact * ) calloc( 1, sizeof( Fact ) );
	    tmp2->num_preconds = 1;
	    tmp2->preconds[0].is_start_end_ovr = w->is_start_end_ovr;
	    tmp2->preconds[0].predicate = w->fact->predicate;
	    for ( i = 0; i < garity[w->fact->predicate]; i++ ) {
	      tmp2->preconds[0].args[i] = w->fact->args[i];
	    }
	  }
      }
      tmp2->effects = instantiate_Effect( o->effects );
      tmp2->next = ghard_mixed_operators;
      ghard_mixed_operators = tmp2;
      gnum_hard_mixed_operators++;
    }
    break;
  case AND:
    tmp2 = new_MixedOperator( o );
    add_or_preconditions_to_mixed_op(tmp2);
    for ( i = 0; i < o->num_vars; i++ ) {
      tmp2->inst_table[i] = linst_table[i];
    }
    m = 0;
    for ( w = tmp1->sons; w; w = w->next )
      if (w->connective != BIN_COMP) m++;
    tmp2->preconds = ( Fact * ) calloc( m, sizeof( Fact ) );
    tmp2->num_preconds = m;
    m = 0;
    for ( w = tmp1->sons; w; w = w->next ) {

      /*
       * DEA - University of Brescia
       */
      
      /**
       * Le precondizioni numeriche vengono inserite come PlNode.
       * Saranno tradotte in seguito.
       **
       * Numeric preconditions are copied as PlNodes.
       * They will be translated after.
       **/
      
      if (w->connective == BIN_COMP)
	{
	  if (!tmp2->numeric)
	    tmp2->numeric = copy_PlNode(w->numeric);
	  else
	    {
	      for (pl = tmp2->numeric; pl && pl->next; pl = pl->next);
	      pl->next =  copy_PlNode(w->numeric);
	    }

	  if (!tmp2->instantiated_vars)
	    tmp2->instantiated_vars = copy_VarList(w->instantiated_vars);
	  else
	    {
	      for (inst_var = tmp2->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
	      inst_var->next = copy_VarList(w->instantiated_vars);
	    }
	  
	  continue;
	}

      /*
       * End of DEA
       */
      tmp2->preconds[m].is_start_end_ovr = w->is_start_end_ovr;
      tmp2->preconds[m].predicate = w->fact->predicate;
      for ( i = 0; i < garity[w->fact->predicate]; i++ ) {
	tmp2->preconds[m].args[i] = w->fact->args[i];
      }
      m++;
    }
    tmp2->effects = instantiate_Effect( o->effects );
    tmp2->next = ghard_mixed_operators;
    ghard_mixed_operators = tmp2;
    gnum_hard_mixed_operators++;
    break;
  case ATOM:
    tmp2 = new_MixedOperator( o );
    add_or_preconditions_to_mixed_op(tmp2);
    for ( i = 0; i < o->num_vars; i++ ) {
      tmp2->inst_table[i] = linst_table[i];
    }
    tmp2->preconds = ( Fact * ) calloc( 1, sizeof( Fact ) );
    tmp2->preconds[0].is_start_end_ovr = tmp1->fact->is_start_end_ovr;
    tmp2->num_preconds = 1;
    tmp2->preconds[0].predicate = tmp1->fact->predicate;
    for ( i = 0; i < garity[tmp1->fact->predicate]; i++ ) {
      tmp2->preconds[0].args[i] = tmp1->fact->args[i];
    }
    tmp2->effects = instantiate_Effect( o->effects );
    tmp2->next = ghard_mixed_operators;
    ghard_mixed_operators = tmp2;
    gnum_hard_mixed_operators++;
    break;
  case TRU:
    tmp2 = new_MixedOperator( o );
    add_or_preconditions_to_mixed_op(tmp2);
    for ( i = 0; i < o->num_vars; i++ ) {
      tmp2->inst_table[i] = linst_table[i];
    }
    tmp2->effects = instantiate_Effect( o->effects );
    tmp2->next = ghard_mixed_operators;
    ghard_mixed_operators = tmp2;
    gnum_hard_mixed_operators++;
    break;

    /*
     * DEA - University of Brescia
     */
    
    /**
     * Le precondizioni numeriche vengono inserite come PlNode.
     * Saranno tradotte in seguito.
     **
     * Numeric preconditions are copied as PlNodes.
     * They will be translated after.
     **/
  case BIN_COMP:
    tmp2 = new_MixedOperator( o );
    add_or_preconditions_to_mixed_op(tmp2);
    if (!tmp2->numeric)
      tmp2->numeric = copy_PlNode(tmp1->numeric);
    else
      {
	for (pl = tmp2->numeric; pl && pl->next; pl = pl->next);
	pl->next =  copy_PlNode(tmp1->numeric);
      }
    if (!tmp2->instantiated_vars)
      tmp2->instantiated_vars = copy_VarList(tmp1->instantiated_vars);
    else
      {
	for (inst_var = tmp2->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
	inst_var->next = copy_VarList(tmp1->instantiated_vars);
      }
    tmp2->effects = instantiate_Effect( o->effects );
    tmp2->next = ghard_mixed_operators;
    ghard_mixed_operators = tmp2;
    gnum_hard_mixed_operators++;
    break;

    /*
     * End of DEA
     */

  default:
    printf("\n\nillegal connective %d in parsing DNF precond.\n\n",
	   tmp1->connective);
    exit( 1 );
  }

  free_WffNode( tmp1 );

}



Effect *instantiate_Effect( Effect *e )

{

  Effect *res = NULL, *tmp, *i;
  Literal *tt, *l;
  int j;

  for ( i = e; i; i = i->next ) {
    tmp = new_Effect();

    for ( j = 0; j < i->num_vars; j++ ) {
      tmp->var_types[j] = e->var_types[j];
    }
    tmp->num_vars = i->num_vars;

    tmp->conditions = instantiate_wff( i->conditions );

    if ( tmp->conditions->connective == FAL ) {
      free_partial_Effect( tmp );
      continue;
    }

    for ( l = i->effects; l; l = l->next ) {
      tt = new_Literal();
      tt->negated = l->negated;
      tt->is_start_end_ovr = l->fact.is_start_end_ovr;
      tt->fact.predicate = l->fact.predicate;
      for ( j = 0; j < garity[tt->fact.predicate]; j++ ) {
	tt->fact.args[j] = l->fact.args[j];
	if ( tt->fact.args[j] < 0 &&
	     linst_table[DECODE_VAR( tt->fact.args[j] )] != -1 ) {
	  tt->fact.args[j] = linst_table[DECODE_VAR( tt->fact.args[j] )];
	}
      }
      tt->next = tmp->effects;
      if ( tmp->effects ) {
	tmp->effects->prev = tt;
      }
      tmp->effects = tt;
    }

    tmp->next = res;
    if ( res ) {
      res->prev = tmp;
    }
    res = tmp;
  }

  return res;

}



WffNode *instantiate_wff( WffNode *w )

{

  WffNode *res = NULL, *tmp, *i;
  int j, c0, c1, m, h;
  Bool ok;

  switch ( w->connective ) {
  case AND:
    m = 0;
    i = w->sons;
    while ( i ) {
      tmp = instantiate_wff( i );
      if ( tmp->connective == FAL ) {
	free_WffNode( res );
	return tmp;
      }
      if ( tmp->connective == TRU ) {
	free( tmp );
	i = i->next;
	continue;
      }
      tmp->next = res;
      if ( res ) {
	res->prev = tmp;
      }
      res = tmp;
      i = i->next;
      m++;
    }
    if ( m == 0 ) {
      res = new_WffNode( TRU );
      break;
    }
    if ( m == 1 ) {
      break;
    }
    tmp = new_WffNode( AND );
    tmp->sons = res;
    res = tmp;
    break;
  case OR:
    m = 0;
    i = w->sons;
    while ( i ) {
      tmp = instantiate_wff( i );
      if ( tmp->connective == TRU ) {
	free_WffNode( res );
	return tmp;
      }
      if ( tmp->connective == FAL ) {
	free( tmp );
	i = i->next;
	continue;
      }
      tmp->next = res;
      if ( res ) {
	res->prev = tmp;
      }
      res = tmp;
      i = i->next;
      m++;
    }
    if ( m == 0 ) {
      res = new_WffNode( FAL );
      break;
    }
    if ( m == 1 ) {
      break;
    }
    tmp = new_WffNode( OR );
    tmp->sons = res;
    res = tmp;
    break;
  case NOT:
    /* must be non-equality
     */
    c0 = ( w->son->fact->args[0] < 0 ) ?
      linst_table[DECODE_VAR( w->son->fact->args[0] )] : w->son->fact->args[0];
    c1 = ( w->son->fact->args[1] < 0 ) ?
      linst_table[DECODE_VAR( w->son->fact->args[1] )] : w->son->fact->args[1];
    if ( c0 < 0 ||
	 c1 < 0 ) {
      /* ef param while checking ef conds in inst op
       */
      res = new_WffNode( ATOM );
      res->fact = new_Fact();
      res->fact->predicate = -2;
      res->fact->args[0] = ( c0 < 0 ) ? w->son->fact->args[0] : c0;
      res->fact->args[1] = ( c1 < 0 ) ? w->son->fact->args[1] : c1;
      break;
    }
    if ( c0 != c1 ) {
      res = new_WffNode( TRU );
    } else {
      res = new_WffNode( FAL );
    }
    break;
  case ATOM:
    if ( w->fact->predicate == -1 ) {
      c0 = ( w->fact->args[0] < 0 ) ?
	linst_table[DECODE_VAR( w->fact->args[0] )] : w->fact->args[0];
      c1 = ( w->fact->args[1] < 0 ) ?
	linst_table[DECODE_VAR( w->fact->args[1] )] : w->fact->args[1];
      if ( c0 < 0 ||
	   c1 < 0 ) {
	/* ef param while checking ef conds in inst op
	 */
	res = new_WffNode( ATOM );
	res->fact = new_Fact();
	res->fact->predicate = -1;
	res->fact->args[0] = c0 < 0 ? w->fact->args[0] : c0;
	res->fact->args[1] = c1 < 0 ? w->fact->args[1] : c1;
	break;
      }
      if ( c0 == c1 ) {
	res = new_WffNode( TRU );
      } else {
	res = new_WffNode( FAL );
      }
      break;
    }
    if ( w->fact->predicate == -2 ) {
      c0 = ( w->fact->args[0] < 0 ) ?
	linst_table[DECODE_VAR( w->fact->args[0] )] : w->fact->args[0];
      c1 = ( w->fact->args[1] < 0 ) ?
	linst_table[DECODE_VAR( w->fact->args[1] )] : w->fact->args[1];
      if ( c0 < 0 ||
	   c1 < 0 ) {
	/* ef param while checking ef conds in inst op
	 */
	res = new_WffNode( ATOM );
	res->fact = new_Fact();
	res->fact->predicate = -1;
	res->fact->args[0] = c0 < 0 ? w->fact->args[0] : c0;
	res->fact->args[1] = c1 < 0 ? w->fact->args[1] : c1;
	break;
      }
      if ( c0 != c1 ) {
	res = new_WffNode( TRU );
      } else {
	res = new_WffNode( FAL );
      }
      break;
    }
    res = new_WffNode( ATOM );
    res->fact = new_Fact();
    res->fact->predicate = w->fact->predicate;
    ok = TRUE;
    for ( j = 0; j < garity[res->fact->predicate]; j++ ) {
      h = ( w->fact->args[j] < 0 ) ?
	linst_table[DECODE_VAR( w->fact->args[j] )] : w->fact->args[j];
      if ( h < 0 ) {
	ok = FALSE;
	res->fact->args[j] = w->fact->args[j];
      } else {
	res->fact->args[j] = h;
      }
    }
    if ( !ok ) {/* contains ef params */
      break;
    }
    if ( !full_possibly_negative( res->fact ) ) {
      free( res->fact );
      res->fact = NULL;
      res->connective = TRU;
      break;
    }
    if ( !full_possibly_positive( res->fact ) ) {
      free( res->fact );
      res->fact = NULL;
      res->connective = FAL;
      break;
    }
    break;

    /*
     * DEA - University of Brescia
     */
    
    /**
     * Le precondizioni numeriche vengono inserite come PlNode.
     * Saranno tradotte in seguito.
     **
     * Numeric preconditions are copied as PlNodes.
     * They will be translated after.
     **/ 
  case BIN_COMP:
    res = new_WffNode(w->connective);
    res->numeric = copy_PlNode(w->numeric);
    res->instantiated_vars = copy_VarList(w->instantiated_vars);
    break;

    /*
     * End of DEA
     */

  case TRU:
  case FAL:
    res = new_WffNode( w->connective );
    break;
  default:
    printf("\n\nillegal connective %d in instantiate formula\n\n",
	   w->connective);
    exit( 1 );
  }

  res->is_start_end_ovr = w->is_start_end_ovr;

  return res;

}



Bool full_possibly_positive( Fact *f )

{

  unsigned long int adr;

  if ( gis_added[f->predicate] ) {
    return TRUE;
  }

  adr = instantiated_fact_adress( f );

  return (check_bit_in_bit_table(lini, f->predicate, adr));

}



Bool full_possibly_negative( Fact *f )

{

  unsigned long int adr;

  if ( gis_deleted[f->predicate] ) {
    return TRUE;
  }

  adr = instantiated_fact_adress( f );

  return (!check_bit_in_bit_table(lini, f->predicate, adr));

}



unsigned long int instantiated_fact_adress( Fact *f )

{

  unsigned long int r = 0;
  int b = 1, i;

  for ( i = 0; i < garity[f->predicate]; i++ ) {
    r += b * f->args[i];
    b *= gnum_constants;
  }

  return r;

}














/*********************************************************
 * CODE THAT MULTIPLIES EFFECT PARAMS --> PSEUDO ACTIONS *
 *********************************************************/















void multiply_hard_effect_parameters( PseudoAction_pointer **ghard_templ, int *gnum_hard_templ )

{

  MixedOperator *o;
  PseudoAction *tmp;
  int i;
  Effect *e;

  (*ghard_templ) = ( PseudoAction_pointer * ) 
    calloc( gnum_hard_mixed_operators, sizeof ( PseudoAction_pointer ) );
  (*gnum_hard_templ) = 0;

  for ( o = ghard_mixed_operators; o; o = o->next ) {
    tmp = new_PseudoAction( o );


    tmp->or_precs = o->or_precs;
    tmp->num_or_precs = o->num_or_precs;
    o->or_precs = NULL;
    o->num_or_precs = 0;
    
    tmp->numeric = o->numeric;
    
    for ( i = 0; i < tmp->l_operator->num_vars; i++ ) {
      linst_table[i] = tmp->inst_table[i];
    }
    
    for ( e = o->effects; e; e = e->next ) {
      create_hard_pseudo_effects( tmp, e, 0 );
    }

    (*ghard_templ)[(*gnum_hard_templ)++] = tmp;
  }
}



void create_hard_pseudo_effects( PseudoAction *a, Effect *e, int curr_var )

{

  int par, t, i, m;
  WffNode *tmp1, *w, *ww;
  PseudoActionEffect *tmp2;

  if ( curr_var < e->num_vars ) {
    par = a->l_operator->num_vars + curr_var;

    t = e->var_types[curr_var];
    for ( i = 0; i < gtype_size[t]; i++ ) {

      if (derived_hard_analisys && lused_const[gtype_consts[t][i]])
	break;

      linst_table[par] = gtype_consts[t][i];
      lused_const[gtype_consts[t][i]] = TRUE;

      create_hard_pseudo_effects( a, e, curr_var + 1 );

      linst_table[par] = -1;
      lused_const[gtype_consts[t][i]] = FALSE;
    }
    return;
  }

  tmp1 = instantiate_wff( e->conditions );

  if ( tmp1->connective == FAL ) {
    free_WffNode( tmp1 );
    return;
  }

  dnf( &tmp1 );
  cleanup_wff( &tmp1 );

  /* only debugging, REMOVE LATER
   */
  if ( is_dnf( tmp1 ) == -1 ) {
    printf("\n\nILLEGAL DNF %s AFTER INSTANTIATION\n\n", a->l_operator->name);
    print_Wff( tmp1, 0 );
    exit( 1 );
  }

  switch ( tmp1->connective ) {
  case OR:
    for ( w = tmp1->sons; w; w = w->next ) {
      tmp2 = new_PseudoActionEffect();
      if ( w->connective == AND ) {
	m = 0;
	for ( ww = w->sons; ww; ww = ww->next ) m++;
	tmp2->conditions = ( Fact * ) calloc( m, sizeof( Fact ) );
	tmp2->num_conditions = m;
	m = 0;
	for ( ww = w->sons; ww; ww = ww->next ) {
	  tmp2->conditions[m].is_start_end_ovr = ww->fact->is_start_end_ovr;
	  tmp2->conditions[m].predicate = ww->fact->predicate;
	  for ( i = 0; i < garity[ww->fact->predicate]; i++ ) {
	    tmp2->conditions[m].args[i] = ww->fact->args[i];
	  }
	  m++;
	}
      } else {
	tmp2->conditions = ( Fact * ) calloc( 1, sizeof( Fact ) );
	tmp2->num_conditions = 1;
	tmp2->conditions[0].is_start_end_ovr = w->fact->is_start_end_ovr;
	tmp2->conditions[0].predicate = w->fact->predicate;
	for ( i = 0; i < garity[w->fact->predicate]; i++ ) {
	  tmp2->conditions[0].args[i] = w->fact->args[i];
	}
      }
      make_instantiate_literals( tmp2, e->effects );
      tmp2->next = a->effects;
      a->effects = tmp2;
      a->num_effects++;
    }
    break;
  case AND:
    tmp2 = new_PseudoActionEffect();
    m = 0;
    for ( w = tmp1->sons; w; w = w->next ) m++;
    tmp2->conditions = ( Fact * ) calloc( m, sizeof( Fact ) );
    tmp2->num_conditions = m;
    m = 0;
    for ( w = tmp1->sons; w; w = w->next ) {
      tmp2->conditions[m].predicate = w->fact->predicate;
      tmp2->conditions[m].is_start_end_ovr = w->fact->is_start_end_ovr;
      for ( i = 0; i < garity[w->fact->predicate]; i++ ) {
	tmp2->conditions[m].args[i] = w->fact->args[i];
      }
      m++;
    }
    make_instantiate_literals( tmp2, e->effects );
    tmp2->next = a->effects;
    a->effects = tmp2;
    a->num_effects++;
    break;
  case ATOM:
    tmp2 = new_PseudoActionEffect();
    tmp2->conditions = ( Fact * ) calloc( 1, sizeof( Fact ) );
    tmp2->num_conditions = 1;
    tmp2->conditions[0].predicate = tmp1->fact->predicate;
    tmp2->conditions[0].is_start_end_ovr = tmp1->fact->is_start_end_ovr;
    for ( i = 0; i < garity[tmp1->fact->predicate]; i++ ) {
      tmp2->conditions[0].args[i] = tmp1->fact->args[i];
    }
    make_instantiate_literals( tmp2, e->effects );
    tmp2->next = a->effects;
    a->effects = tmp2;
    a->num_effects++;
    break;
  case TRU:
    tmp2 = new_PseudoActionEffect();
    make_instantiate_literals( tmp2, e->effects );
    tmp2->next = a->effects;
    a->effects = tmp2;
    a->num_effects++;
    break;
  default:
    printf("\n\nillegal connective %d in parsing DNF precond.\n\n",
	   tmp1->connective);
    exit( 1 );
  }

  free_WffNode( tmp1 );

}
 


void make_instantiate_literals( PseudoActionEffect *e, Literal *ll )

{

  int ma = 0, md = 0, i;
  Literal *l;

  for ( l = ll; l; l = l->next ) {
    if ( l->negated ) {
      md++;
    } else {
      ma++;
    }
  }

  e->adds = ( Fact * ) calloc( ma, sizeof( Fact ) );
  e->dels = ( Fact * ) calloc( md, sizeof( Fact ) );

  for ( l = ll; l; l = l->next ) {
    if ( l->negated ) {
      e->dels[e->num_dels].predicate = l->fact.predicate;
      e->dels[e->num_dels].is_start_end_ovr = l->fact.is_start_end_ovr;
      for ( i = 0; i < garity[l->fact.predicate]; i++ ) {
	e->dels[e->num_dels].args[i] = ( l->fact.args[i] < 0 ) ?
	  linst_table[DECODE_VAR( l->fact.args[i] )] : l->fact.args[i];
      }
      e->num_dels++;
    } else {
      e->adds[e->num_adds].predicate = l->fact.predicate;
      e->adds[e->num_adds].is_start_end_ovr = l->fact.is_start_end_ovr;
      for ( i = 0; i < garity[l->fact.predicate]; i++ ) {
	e->adds[e->num_adds].args[i] = ( l->fact.args[i] < 0 ) ?
	  linst_table[DECODE_VAR( l->fact.args[i] )] : l->fact.args[i];
      }
      e->num_adds++;
    }
  }

}

