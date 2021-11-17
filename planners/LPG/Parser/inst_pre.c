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



/**
   The following parts of this file have been modified by the 
   LPG developers (DEA - University of Brescia):

   Included libraries:
   - lpg.h
   - inst_utils.h
   - LpgOutput.h
  
   Modified functions:
   - encode_domain_in_integers
   - collect_all_strings
   - create_integer_representation
   - make_Fact
   - make_Wff
   - normalize_all_wffs
**/













/*********************************************************************
 * File: inst_pre.c
 * Description: functions for instantiating operators, preprocessing part.
 *              - transform domain into integers
 *              - inertia preprocessing:
 *                  - collect inertia info
 *                  - split initial state in special arrays
 *              - Wff normalization:
 *                  - simplification
 *                  - quantifier expansion
 *                  - NOT s down
 *              - negative preconditions translation
 *              - split operators into easy and hard to instantiate
 *
 *              - full DNF functions, only feasible for fully instantiated
 *                formulae
 *
 * Author: Joerg Hoffmann 2000
 *
 *********************************************************************/ 









#include "ff.h"

#include "output.h"
#include "memory.h"

#include "inst_pre.h"

/*
 * DEA - University of Brescia
 */


#include "lpg.h" 
#include "parse.h"
#include "inst_utils.h"
#include "LpgOutput.h"
#include "inst_easy.h"


Bool save_rule_precond = FALSE;
int rule_num;
int **rules_precs = NULL;

/*
 * End of DEA
 */














/*******************************************************
 * TRANSFORM DOMAIN INTO INTEGER (FACT) REPRESENTATION *
 *******************************************************/









// char *lvar_names[MAX_VARS];
// int lvar_types[MAX_VARS];










void encode_domain_in_integers( void )

{

  int i,j;

  collect_all_strings();

  if ( gcmd_line.display_info == 103 ) {
    printf("\nconstant table:");
    for ( i = 0; i < gnum_constants; i++ ) {
      printf("\n%d --> %s", i, gconstants[i]);
    }

    printf("\n\ntypes table:");
    for ( i = 0; i < gnum_types; i++ ) {
      printf("\n%d --> %s: ", i, gtype_names[i]);
      for ( j = 0; j < gtype_size[i]; j++ ) {
	printf("%d ", gtype_consts[i][j]);
      }
    }

    printf("\n\npredicates table:");
    for ( i = 0; i < gnum_predicates; i++ ) {
      printf("\n%3d --> %s: ", i, gpredicates[i]);
      for ( j = 0; j < garity[i]; j++ ) {
	printf("%s ", gtype_names[gpredicates_args_type[i][j]]);
      }
    }
/**
 * DEA - University of Brescia
 **/

      printf ("\n\nfunctions table:");
      for (i = 0; i < gnum_functions; i++) {
	printf ("\n%3d --> %s: ", i, gfunctions[i]);
	for (j = 0; j < gfunarity[i]; j++) {
	  printf ("%s ", gtype_names[gfunctions_args_type[i][j]]);
	}
      }

/**
 * End of DEA
 **/
    printf("\n\n");
  }

  create_integer_representation();

  if (GpG.derived_predicates)
    {
      GpG.recursive_rules = check_for_recursive_rules();

      //Abilito il pruning se non � stato disabilitato da linea di comando e le regole sono ricorsive
      GpG.derived_pruning_on = (!GpG.disable_pruning && GpG.recursive_rules);

      if (GpG.derived_pruning_on)
	printf("\nRecursive derived predicates: pruning ON");
    }

  
  if ( gcmd_line.display_info == 104 ) {
    printf("\n\nfirst step initial state is:");
    for ( i = 0; i < gnum_full_initial; i++ ) {
      printf("\n");
      print_Fact( &(gfull_initial[i]) );
    }
/**
 * DEA - University of Brescia
 **/

      printf ("\n\nnumeric variables:");
      for (i = 0; i < gnum_fullnum_initial; i++) {
	printf ("\n");
	print_NumVar ((gfullnum_initial[i]), i, -1);
      }

/**
 * End of DEA
 **/
    
    printf("\n\nfirst step operators are:");
    for ( i = 0; i < gnum_operators; i++ ) {
      print_Operator( goperators[i] );
    }
    printf("\n\n");

    printf("\n\nfirst step goal is:\n");
    print_Wff( ggoal, 0 );
  }

}



void collect_all_strings( void )

{

  FactList *f;
  TokenList *t;
  int p_num, type_num, c_num, ar;
  int i;

  for ( f = gorig_constant_list; f; f = f->next ) {
    if ( (type_num = position_in_types_table( f->item->next->item )) == -1 ) {
      if ( gnum_types == MAX_TYPES ) {
	printf("\ntoo many types! increase MAX_TYPES (currently %d)\n\n",
	       MAX_TYPES);
	exit( 1 );
      }
      gtype_names[gnum_types] = new_Token( strlen( f->item->next->item ) + 1 );
      strcpy( gtype_names[gnum_types], f->item->next->item );
      gtype_size[gnum_types] = 0;
      for ( i = 0; i < MAX_CONSTANTS; i++ ) {
	gis_member[i][gnum_types] = FALSE;
      }
      type_num = gnum_types++;
    }

    if ( (c_num = position_in_constants_table( f->item->item )) == -1 ) {
      if ( gnum_constants == MAX_CONSTANTS ) {
	printf("\ntoo many constants! increase MAX_CONSTANTS (currently %d)\n\n",
	       MAX_CONSTANTS);
	exit( 1 );
      }
      gconstants[gnum_constants] = new_Token( strlen( f->item->item ) + 1 );
      strcpy( gconstants[gnum_constants], f->item->item );
      c_num = gnum_constants++;
    }
    
    if ( !gis_member[c_num][type_num] ) {
      if ( gtype_size[type_num] == MAX_TYPE ) {
	printf("\ntoo many consts in type %s! increase MAX_TYPE (currently %d)\n\n",
	       gtype_names[type_num], MAX_TYPE);
	exit( 1 );
      }     
      gtype_consts[type_num][gtype_size[type_num]++] = c_num;
      gis_member[c_num][type_num] = TRUE;
    }
  }

/*
 * DEA - University of Brescia
 */

  /* crea un predicato fittizio per evitare di scartare operatori con soli effetti numerici */
  gpredicates[gnum_predicates] = new_Token (strlen (DUMMY_PRED_STRING) + 1);
  GpG.dummy_pos = gnum_predicates;
  strcpy (gpredicates[gnum_predicates], DUMMY_PRED_STRING);
  garity[gnum_predicates++] = 0;

/*
 * End of DEA
 */

  for ( f = gpredicates_and_types; f; f = f->next ) {
    if ( (p_num = position_in_predicates_table( f->item->item )) != -1 ) {
      printf("\npredicate %s declared twice!\n\n", f->item->item);
      exit( 1 );
    }
    if ( gnum_predicates == MAX_PREDICATES ) {
      printf("\ntoo many predicates! increase MAX_PREDICATES (currently %d)\n\n",
	     MAX_PREDICATES);
      exit( 1 );
    }
    gpredicates[gnum_predicates] = new_Token( strlen( f->item->item ) + 1 );
    strcpy( gpredicates[gnum_predicates], f->item->item );
    ar = 0;
    for ( t = f->item->next; t; t = t->next ) {
      if ( (type_num = position_in_types_table( t->item )) == -1 ) {
	printf("\nWARNING: predicate %s is declared to use unknown or empty type %s\n\n", 
	       f->item->item, t->item);
	continue;
	//exit( 1 );
      }
      if ( ar == MAX_ARITY ) {
	printf("\narity of %s to high! increase MAX_ARITY (currently %d)\n\n",
	       gpredicates[gnum_predicates], MAX_ARITY);
	exit( 1 );
      }
      gpredicates_args_type[gnum_predicates][ar++] = type_num;
    }
    garity[gnum_predicates++] = ar;
  }



/*
 * DEA - University of Brescia
 */

  /* crea una funzione fittizia per evitare sovrapposizioni di concetti diversi (fatti e cvar) con indice zero */

  gfunctions[gnum_functions] = new_Token (strlen (DUMMY_VAR_STRING) + 1);
  strcpy (gfunctions[gnum_functions], DUMMY_VAR_STRING);
  gfunarity[gnum_functions++] = 0;

  /* crea una funzione fittizia per esprimere il costo totale */

  gfunctions[gnum_functions] =
    new_Token (strlen (INTERNAL_TOTAL_COST_STRING) + 1);
  strcpy (gfunctions[gnum_functions], INTERNAL_TOTAL_COST_STRING);
  gfunarity[gnum_functions++] = 0;

  /* crea una funzione fittizia per esprimere il tempo totale */

  gfunctions[gnum_functions] = new_Token (strlen (TOTAL_TIME_STRING) + 1);
  strcpy (gfunctions[gnum_functions], TOTAL_TIME_STRING);
  gfunarity[gnum_functions++] = 0;


  for (f = gfunctions_and_types; f; f = f->next) {
    if ((p_num = position_in_functions_table (f->item->item)) != -1) {
      printf ("\npredicate %s declared twice!\n\n", f->item->item);
      exit (1);
    }
    if (gnum_functions == MAX_FUNCTIONS) {
      printf("\ntoo many functions! increase MAX_FUNCTIONS (currently %d)\n\n", MAX_FUNCTIONS);
      exit (1);
    }
    gfunctions[gnum_functions] = new_Token (strlen (f->item->item) + 1);
    strcpy (gfunctions[gnum_functions], f->item->item);
    ar = 0;

    for (t = f->item->next; t; t = t->next) {
      if ((type_num = position_in_types_table (t->item)) == -1) {
	printf("\nWARNING: predicate %s is declared to use unknown or empty type %s\n\n", f->item->item, t->item);
	continue;
	//exit (1);
      }
      if (ar == MAX_ARITY) {
	printf("\narity of %s to high! increase MAX_ARITY (currently %d)\n\n",gfunctions[gnum_functions], MAX_ARITY);
	exit (1);
      }
      gfunctions_args_type[gnum_functions][ar++] = type_num;
    }
    gfunarity[gnum_functions++] = ar;
  }


/*
 * End of DEA
 */


  free_FactList( gorig_constant_list );
  free_FactList( gpredicates_and_types );
/*
 * DEA - University of Brescia
 */
  free_FactList (gfunctions_and_types);
/*
 * End of DEA
 */

}



int position_in_types_table( char *str )

{

  int i;

  for ( i=0; i<gnum_types; i++ ) {
    if ( str == gtype_names[i] || 
	 (strcmp( str, gtype_names[i] ) == SAME) ) {
      return i;
    }
  }

  return -1;

}



int position_in_constants_table( char *str )

{

  int i;

  for ( i=0; i<gnum_constants; i++ ) {
    if ( str == gconstants[i] || 
	 strcmp( str, gconstants[i] ) == SAME ) {
      return i;
    }
  }

  return -1;

}



int position_in_predicates_table( char *str )

{

  int i;

  for ( i=0; i<gnum_predicates; i++ ) {
    if ( str == gpredicates[i] || 
	 strcmp( str, gpredicates[i] ) == SAME ) {
      return i;
    }
  }

  return -1;

}


int name_in(char *name, char **a, int max) {
  int result = 0, i;
  for (i = 0; i < max; i++) {
    result = (strcmp(name, a[i]) == SAME);
    if (result) break;
  }
  return result;
}


/*
 * DEA - University of Brescia
 */

/**
 * Conta le variabili che compaiono all'interno di un PlNode
 **
 * Count the number of variables in a PlNode 
 **/
int search_variables(PlNode *p, int *i) {
  int predicate = -1, arg = 0;
  TokenList *tk;
  TypedList *aux;
  
  if (!p)
    return (*i);

  if (p->parse_vars)
    for (aux=p->parse_vars; aux; aux=aux->next)
      if (!name_in(aux->name, lvar_names, *i)) {
	lvar_names[*i] = aux->name;
	lvar_types[*i] = position_in_types_table(aux->type->item);
	(*i)++;
      }

  switch (p -> connective) {
  case ATOM : 
    arg = 0;
    predicate = position_in_predicates_table(p -> atom -> item);
    for (tk = p -> atom -> next; tk; tk = tk -> next)
      if (tk -> item[0] == '?') {
	if (!name_in(tk -> item, lvar_names, *i)) {
	  lvar_names[*i] = tk -> item;
	  lvar_types[*i] = gpredicates_args_type[predicate][arg];
	  (*i)++;
	}
	arg++;
      }
    if (p -> next)
      search_variables(p -> next, i);
    break;
  case AND :
  case OR :
  case NOT : {
    search_variables(p -> sons, i);
    break;
  }
  case ALL :
  case EX :
    //search_variables(p -> sons, i);
    search_variables(p -> next, i);
    break;
  case WHEN :
    search_variables(p -> sons, i);
    search_variables(p -> next, i);
    break;
  case TRU :
  case FAL :
    break;
  default :
    printf("Warning : unexpected connective %d in derived predicate goal definition.", p -> connective);
  }
  
  return (*i);
  
}



/**
 * Elimina i doppioni dai fatti iniziali
 **
 * Clean initial facts
 **/
void cleanup_full_initial( void ) {

  int i, j;

  for (i = 0; i < gnum_full_initial - 1; i++) {
    for (j = i + 1; j < gnum_full_initial; j++) {
      if (identical_fact(&gfull_initial[i], &gfull_initial[j])) {
	gfull_initial[j] = gfull_initial[--gnum_full_initial];
	
	/* Check the moved fact
	 */
	j--;

      }
    }
  }

}


/*
 * End of DEA
 */ 

void create_integer_representation( void )

{

  PlNode *n, *nn;
  PlOperator *o;
  Operator *tmp;
  FactList *ff;
  WffNode *w;
  int type_num, i, k, j;

  if ( gorig_initial_facts ) {
    for ( n = gorig_initial_facts->sons; n; n = n->next ) {
      if ( gnum_full_initial == MAX_INITIAL ) {
	printf("\ntoo many initial facts! increase MAX_INITIAL (currently %d)\n\n", MAX_INITIAL);
	exit( 1 );
      }
      
      /*
       * DEA - University of Brescia
       */
      
      if (n->atom || n->connective == NOT) {
	
	/*
	 * End of DEA
	 */
	
	make_Fact( &(gfull_initial[gnum_full_initial]), n, 0 );
	if ( gfull_initial[gnum_full_initial].predicate == -1 ) {
	  printf("\nequality in initial state! check input files.\n\n");
	  exit( 1 );
	}
	
	if (DEBUG1) 
	  {
	    print_Fact(&gfull_initial[gnum_full_initial]);
	    printf(" %d\n", gnum_full_initial);
	  }
	
	gnum_full_initial++;
      }
    } // End for

    /*
     * DEA - University of Brescia
     */
   
    cleanup_full_initial();

    reset_numvar_hash_table();
 
    /*inserisce d'ufficio la variabile primaria dummy */
    
    if (gfullnum_initial==NULL) {
      gfullnum_initial = (NumVar **) calloc (max_num_value, sizeof(NumVar *));
      memset(gfullnum_initial, 0, max_num_value * sizeof(NumVar *));
    }

    if (gfullnum_initial[gnum_fullnum_initial] == NULL) {
      gfullnum_initial[gnum_fullnum_initial] = (NumVar *) calloc (1, sizeof (NumVar));
    }

    gfullnum_initial[gnum_fullnum_initial]->function = DUMMY_VAR_INDEX;
    insert_numvar_in_hash_table(gfullnum_initial[gnum_fullnum_initial], gnum_fullnum_initial);

    make_compvar (&(gcomp_var[gnum_comp_var]), gnum_comp_var, (gfullnum_initial[gnum_fullnum_initial]), gnum_fullnum_initial);
    // hash
    gcomp_var[gnum_comp_var].position = gnum_comp_var;
    /* aggiungo in hash questa cvar */
    insert_cvar_in_hash (&(gcomp_var[gnum_comp_var]));
   
    gnum_comp_var++;             // == 1 (Prima variabile inserita)
    gnum_fullnum_initial++;      // == 1
    //      assert (gnum_comp_var < MAX_NUM_INC);
    //      assert (gnum_fullnum_initial < max_num_initial);

    /* inserisce d'ufficio la variabile primaria total-cost */

    if (gfullnum_initial[gnum_fullnum_initial] == NULL) {
	gfullnum_initial[gnum_fullnum_initial] = (NumVar *) calloc (1, sizeof (NumVar));
    }

    gfullnum_initial[gnum_fullnum_initial]->function = INTERNAL_TOTAL_COST_FUNCTION_INDEX;
    insert_numvar_in_hash_table(gfullnum_initial[gnum_fullnum_initial], gnum_fullnum_initial);

    make_compvar (&(gcomp_var[gnum_comp_var]), gnum_comp_var,(gfullnum_initial[gnum_fullnum_initial]), gnum_fullnum_initial);
    // hash
    gcomp_var[gnum_comp_var].position = gnum_comp_var;
    /* aggiungo in hash questa cvar */
    insert_cvar_in_hash (&(gcomp_var[gnum_comp_var]));

    gnum_comp_var++;          // == 2 Seconda variabile inserita
    gnum_fullnum_initial++;   // == 2

    //      assert (gnum_comp_var < MAX_NUM_INC);
    //      assert (gnum_fullnum_initial < max_num_initial);

    /*inserisce d'ufficio la variabile primaria total-time */

    if (gfullnum_initial[gnum_fullnum_initial] == NULL) {
      gfullnum_initial[gnum_fullnum_initial] = (NumVar *) calloc (1, sizeof (NumVar));
    }

    gfullnum_initial[gnum_fullnum_initial]->function = TOTAL_TIME_FUNCTION_INDEX;
    insert_numvar_in_hash_table(gfullnum_initial[gnum_fullnum_initial], gnum_fullnum_initial);

    make_compvar (&(gcomp_var[gnum_comp_var]), gnum_comp_var, (gfullnum_initial[gnum_fullnum_initial]), gnum_fullnum_initial);
    // hash
    gcomp_var[gnum_comp_var].position = gnum_comp_var;
    /* aggiungo in hash questa cvar */
    insert_cvar_in_hash (&(gcomp_var[gnum_comp_var]));

    gnum_comp_var++;           //  == 3 Terza variabile inserita
    gnum_fullnum_initial++;    //  == 3

    //      assert (gnum_comp_var < MAX_NUM_INC);
    //      assert (gnum_fullnum_initial < max_num_initial);

    /* Fine inserimento variabili d'ufficio */
    /****************************************/

    /*
      Nel ciclo for gnum_comp_var e gnum_fullnum_initial crescono insieme : se superano max_num_value devo riallocare tutti i vettori
      --> attenzione al bitarray gis_inertial
    */

    for (n = gorig_initial_facts->sons; n; n = n->next) {
     
      /*
	Se necessario rialloco la memoria.
	
	NB.
	    Rialloco se gnum_fullnum_initial � pari a max_num_value-1 perch� gli effetti numerici (in gcomp_var_effects)
	    assumeranno indici da 1 in poi (manca lo zero, perch� poi saranno usati indici negativi, a partire da -1,
	    per distinguerli dai fatti booleani). Quindi l'ultimo effetto inserito � quello in gnum_fullnum_initial
	    e NON in gnum_fullnum_initial - 1 !|
      */
      if (gnum_fullnum_initial >= max_num_value - 1) {
	max_num_value += MAX_NUM_INC;
	max_fullnum_initial = max_num_value;

	gcomp_var = (CompositeNumVar *) realloc(gcomp_var, max_num_value * sizeof(CompositeNumVar));
	memset ( &gcomp_var[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(CompositeNumVar));

	gcomp_var_value = (float *) realloc(gcomp_var_value, max_num_value * sizeof(float));
	memset ( &gcomp_var_value[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(float));

	gcomp_var_value_before = (float *) realloc(gcomp_var_value_before, max_num_value * sizeof(float));
	memset ( &gcomp_var_value_before[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(float));

	gfullnum_initial = (NumVar **) realloc (gfullnum_initial, max_num_value * sizeof(NumVar *));
	memset (&gfullnum_initial[max_num_value - MAX_NUM_INC], 0, MAX_NUM_INC * sizeof(NumVar *));

	gcomp_var_effects = (CompositeNumVar *) realloc(gcomp_var_effects, max_num_value * sizeof(CompositeNumVar));
	memset ( &gcomp_var_effects[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(CompositeNumVar));

	/*
	  In questa fase gis_inertial non viene utilizzato : posso riallocarlo e resettarlo completamente
	  (potrei anche farlo dopo fuori dal ciclo... ma cos� tutte le realloc sono insieme)
	*/
	gis_inertial = (int*) realloc (gis_inertial, ((max_num_value>>5) + 1) * sizeof(int));
	memset (gis_inertial, 0, ((max_num_value>>5) + 1) * sizeof(int));

      }

      if (n->connective == EQUAL_CONN) {

	if (gfullnum_initial[gnum_fullnum_initial] == NULL) {
	  gfullnum_initial[gnum_fullnum_initial] = (NumVar *) calloc (1, sizeof (NumVar));
	}

	make_VarAssign ((gfullnum_initial[gnum_fullnum_initial]), n, 0);
	insert_numvar_in_hash_table(gfullnum_initial[gnum_fullnum_initial], gnum_fullnum_initial);

	make_compvar (&(gcomp_var[gnum_comp_var]), gnum_comp_var,(gfullnum_initial[gnum_fullnum_initial]),gnum_fullnum_initial);
	
	// hash
	gcomp_var[gnum_comp_var].position = gnum_comp_var;

	/* aggiungo in hash questa cvar */
	insert_cvar_in_hash (&(gcomp_var[gnum_comp_var]));
	if (gfullnum_initial[gnum_fullnum_initial]->function == -1) {
	  printf ("\nequality in initial state! check input files.\n\n");
	  exit (1);
	}

	gnum_comp_var++;
	gnum_fullnum_initial++;
	//	  assert (gnum_comp_var < MAX_NUM_INC);
	//	  assert (gnum_fullnum_initial < max_num_initial);

	if (gnum_comp_var >= max_num_value ) {
	  max_num_value += MAX_NUM_INC;
	  
	  gcomp_var = (CompositeNumVar *) realloc(gcomp_var, max_num_value * sizeof(CompositeNumVar));
	  memset ( &gcomp_var[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(CompositeNumVar));

	  gcomp_var_value = (float *) realloc(gcomp_var_value, max_num_value * sizeof(float));
	  memset ( &gcomp_var_value[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(float));

	  gcomp_var_value_before = (float *) realloc(gcomp_var_value_before, max_num_value * sizeof(float));
	  memset ( &gcomp_var_value_before[max_num_value - MAX_NUM_INC] , 0, MAX_NUM_INC * sizeof(float));

	  gfullnum_initial = (NumVar **) realloc (gfullnum_initial, max_num_value * sizeof(NumVar *));
	  memset (&gfullnum_initial[max_num_value - MAX_NUM_INC], 0, MAX_NUM_INC * sizeof(NumVar *));

	  gis_inertial = (int*) realloc (gis_inertial, (max_num_value / 32) * sizeof(int));
	  memset (&gis_inertial[ (max_num_value - MAX_NUM_INC) / 32], 0, (MAX_NUM_INC / 32) * sizeof(int));
	}

      }
    }

    
    /*
     * End of DEA
     */


    free_PlNode( gorig_initial_facts );

  }

  ggoal = make_Wff( gorig_goal_facts, 0 );
  if (GpG.timed_facts_present)
    {
      timed_wff = make_Wff(timed_nodes, 0);
      w = timed_wff;
      for (n = timed_nodes->next; n; n = n->next)
	{
	  w->next = make_Wff(n, 0);
	  w = w->next;
	}
    }

  for ( o = gloaded_ops; o; o = o->next ) {
    tmp = new_Operator( o->name, o->number_of_real_params );

    tmp->ops_type = o->ops_type;

    for ( ff = o->params; ff; ff = ff->next ) {
      if ( (type_num = position_in_types_table( ff->item->next->item )) == -1 ) {
	printf("\nwarning: parameter %s of op %s has unknown or empty type %s. skipping op",
	       ff->item->item, o->name, ff->item->next->item);
	break;
      }
      if ( tmp->num_vars == MAX_VARS ) {
	printf("\ntoo many parameters! increase MAX_VARS (currently %d)\n\n",
	       MAX_VARS);
	exit( 1 );
      }
      for ( i = 0; i < tmp->num_vars; i++ ) {
	if ( tmp->var_names[i] == ff->item->item ||
	     strcmp( tmp->var_names[i], ff->item->item ) == SAME ) {
	  printf("\nwarning: operator %s parameter %s overwrites previous declaration\n\n",
		 tmp->name, ff->item->item);
	}
      }
      tmp->var_names[tmp->num_vars] = new_Token( strlen( ff->item->item ) + 1 );
      strcpy( tmp->var_names[tmp->num_vars], ff->item->item );
      tmp->var_types[tmp->num_vars++] = type_num;
    }
    if ( ff ) {
      free_Operator( tmp );
      continue;
    }

    for ( i = 0; i < tmp->num_vars; i++ ) {
      lvar_types[i] = tmp->var_types[i];
      lvar_names[i] = tmp->var_names[i];
    }

    tmp->preconds = make_Wff( o->preconds, tmp->num_vars );

    if ( o->effects ) {
      nn = o->effects->sons;
      while ( nn &&
	      (tmp->effects = make_effect( nn, tmp->num_vars )) == NULL ) {
	nn = nn->next;
      }
      if ( nn ) {
	for ( n = nn->next; n; n = n->next ) {
	  if ( (tmp->effects->prev = make_effect( n, tmp->num_vars )) == NULL ) {
	    continue;
	  }
	  tmp->effects->prev->next = tmp->effects;
	  tmp->effects = tmp->effects->prev;
	}
      }
    }

    if ( gnum_operators == MAX_OPERATORS ) {
      printf("\ntoo many operators! increase MAX_OPERATORS (currently %d)\n\n",
	     MAX_OPERATORS);
      exit( 1 );
    }
    goperators[gnum_operators++] = tmp;
  }

  if ( 0 ) {
    /* currently not in use; leads to free memory reads and
     * free memory frees (no memory leaks), which are hard to explain.
     *
     * almost no memory consumption anyway.
     */
    free_PlOperator( gloaded_ops );
  }

  // Setto tutti i predicati come predicati "di base"
  memset(gpredicates_type, IS_BASE, MAX_PREDICATES * sizeof(int));

  if (GpG.derived_predicates) {
    
    int pred_blocks = (gnum_predicates >> 5) + 1;

    rules_precs = alloc_matrix(gnum_derived_predicates, pred_blocks);

    k = 0;
    for ( o = gderived_predicates; o; o = o->next ) {

      tmp = new_Operator( o->name, o->number_of_real_params );

      tmp->ops_type = DERIVED_OP;

      j = position_in_predicates_table(o -> name);
      if (j < 0) {
	printf("\nUndefined predicate %s found.", o -> name);
	exit(1);
      }
      // Ho trovato un predicato derivato -> Setto il predicato corrispondente in gpredicates
      // come "derivato"
      gpredicates_type[j] = IS_DERIVED;

      for ( ff = o->params; ff; ff = ff->next ) {
	if ( (type_num = position_in_types_table( ff->item->next->item )) == -1 ) {
	  printf("\nwarning: parameter %s of op %s has unknown or empty type %s. skipping op",
		 ff->item->item, o->name, ff->item->next->item);
	  break;
	}
	if ( tmp->num_vars == MAX_VARS ) {
	  printf("\ntoo many parameters! increase MAX_VARS (currently %d)\n\n",
		 MAX_VARS);
	  exit( 1 );
	}
	for ( i = 0; i < tmp->num_vars; i++ ) {
	  if ( tmp->var_names[i] == ff->item->item ||
	       strcmp( tmp->var_names[i], ff->item->item ) == SAME ) {
	    printf("\nwarning: operator %s parameter %s overwrites previous declaration\n\n",
		   tmp->name, ff->item->item);
	  }
	}
	tmp->var_names[tmp->num_vars] = new_Token( strlen( ff->item->item ) + 1 );
	strcpy( tmp->var_names[tmp->num_vars], ff->item->item );
	tmp->var_types[tmp->num_vars++] = type_num;
      }
      if ( ff ) {
	free_Operator( tmp );
	continue;
      }

      
      for ( i = 0; i < tmp->num_vars; i++ ) {
	lvar_types[i] = tmp->var_types[i];
	lvar_names[i] = tmp->var_names[i];
      }

      save_rule_precond = TRUE;
     
      rule_num = k;
      
      tmp->preconds = make_Wff( o->preconds, tmp->num_vars );

      save_rule_precond = FALSE; 

      if ( o->effects ) {
	nn = o->effects->sons;
	while ( nn &&
		(tmp->effects = make_effect( nn, tmp->num_vars )) == NULL ) {
	  nn = nn->next;
	}
	if ( nn ) {
	  for ( n = nn->next; n; n = n->next ) {
	    if ( (tmp->effects->prev = make_effect( n, tmp->num_vars )) == NULL ) {
	      continue;
	    }
	    tmp->effects->prev->next = tmp->effects;
	    tmp->effects = tmp->effects->prev;
	  }
	}
      }
      
      if ( k == MAX_DERIVED_PREDICATES ) {
	printf("\ntoo many derived predicates! increase MAX_DERIVED_PREDICATES (currently %d)", MAX_DERIVED_PREDICATES);
	printf("\nNedeed : %d\n\n", gnum_derived_predicates);
	fflush(stdout);
	exit( 1 );
      }

      gderivedpred[k++] = tmp;
    }

    if (k != gnum_derived_predicates) 
      printf("Error : found %d derived predicates instead of %d", k, gnum_derived_predicates);

    if ( 0 ) {
      /* currently not in use; leads to free memory reads and
       * free memory frees (no memory leaks), which are hard to explain.
       *
       * almost no memory consumption anyway.
       */
      free_PlOperator( gderived_predicates );
    }

   

  }    

  /*
   * DEA - University of Brescia
   */

  gnum_fullnum_blocks = gnum_fullnum_initial / 32 + 1;


  /*
   * End of DEA
   */

}

/*
 * DEA - University of Brescia
 */

/**
 * Elimino dai fatti iniziali i nodi che rappresentano fatti temporizzati
 **
 * Delete timed facts nodes from initial facts 
 **/
void clear_Timed_Fact_Nodes( void ) {
  PlNode *n, *prev, *to_del;
  prev = NULL;
  to_del = NULL;
  gnum_timed_initial = 0;
  n = gorig_initial_facts -> sons;
  while (n) {
    if (n -> connective == TIMED_FACT) {
      to_del = n;
      gnum_timed_initial++; 
      if (!prev)
	gorig_initial_facts -> sons = n -> next;
      else
        prev -> next = n -> next;
      n = n -> next;

      to_del->value = atof(to_del->sons->next->atom->item);
      free_PlNode(to_del->sons->next);
      to_del->sons->next = NULL;

      to_del -> next = timed_nodes;
      timed_nodes = to_del;
    }
    else {
      prev = n;
      n = n -> next;
    }
  }
}

void add_Timed_Facts_to_ops( PlOperator **ops ) {
  PlNode *n, *pln;
  PlOperator *op;
  char *name;
  for (n = gorig_initial_facts -> sons; n; n = n-> next) {
    if (n -> connective == TIMED_FACT) {
      name = (char *)calloc(strlen(n -> sons -> next -> atom -> item) + 12, sizeof(char));
      sprintf(name, "TIMED_FACT-");
      strcat(name, n -> sons -> next -> atom -> item);
      op = new_PlOperator(name);
      op -> ops_type = TIMED_FACT_ACT; 
      op -> effects = cp_PlNode(n -> sons);
      free_PlNode(op -> effects -> next);
      op -> effects -> next = NULL;
      
      pln =  new_PlNode(DURATION_CONSTRAINT_CONN);
      pln -> sons = new_PlNode(EQUAL_CONN);
      pln -> sons -> sons = new_PlNode(DURATION_VAR_ATOM);
      pln -> sons -> sons -> next = cp_PlNode(n -> sons -> next);
      
      op -> duration = new_PlNode(AND);
      op -> duration -> sons = pln;
      op -> duration -> value = atof(n -> sons -> next -> atom -> item);
      
      op -> next = (*ops);
      (*ops) = op;
    }
  }
}



/*
 * End of DEA
 */ 


void make_Fact( Fact *f, PlNode *n, int num_vars )

{

  int m, i;
  TokenList *t;

  if ( !n->atom ) {
    /* can't happen after previous syntax check. Oh well, whatever...
     */
    printf("\nillegal (empty) atom used in domain. check input files\n\n");
    exit( 1 );
  }
  /*
   * DEA - University of Brescia
   */
  if (n->atom) {
  /*
   * End of DEA
   */
  if ( strcmp( n->atom->item, EQ_STR ) == SAME ) {
    f->predicate = -1;
  } else {
    f->predicate = position_in_predicates_table( n->atom->item );
    if ( f->predicate == -1 ) {
      printf("\nundeclared predicate %s used in domain definition\n\n",
	     n->atom->item);
      exit( 1 );
    }
  }

  m = 0;
  for ( t = n->atom->next; t; t = t->next ) {
    if ( t->item[0] == '?' ) {
      for ( i=num_vars-1; i>-1; i-- ) {
	/* downwards, to always get most recent declaration/quantification
	 * of that variable
	 */
	if ( lvar_names[i] == t->item ||
	     strcmp( lvar_names[i], t->item ) == SAME ) {
	  break;
	}
      }
      if ( i == -1 ) {
	printf("\nundeclared variable %s in literal %s. check input files\n\n",
	       t->item, n->atom->item);
	exit( 1 );
      }
      if ( f->predicate != -1 &&
	   lvar_types[i] != gpredicates_args_type[f->predicate][m] &&
	   !is_subtype( lvar_types[i], gpredicates_args_type[f->predicate][m] ) ) {
	printf("\ntype of var %s does not match type of arg %d of predicate %s\n\n",
	       lvar_names[i], m, gpredicates[f->predicate]);
	exit( 1 );
      }
      f->args[m] = ENCODE_VAR( i );
    } else {
      if ( (f->args[m] = 
	    position_in_constants_table( t->item )) == -1 ) {
	printf("\nunknown constant %s in literal %s. check input files\n\n",
	       t->item, n->atom->item);
	exit( 1 );
      }
      if ( f->predicate != -1 &&
	   !gis_member[f->args[m]][gpredicates_args_type[f->predicate][m]] ) {
	printf("\ntype mismatch: constant %s as arg %d of %s. check input files\n\n",
	       gconstants[f->args[m]], m, gpredicates[f->predicate]);
	exit( 1 );
      }
    }
    m++;
  }
  if ( f->predicate == -1 ) {
    if ( m != 2 ) {
      printf("\nfound eq - predicate with %d arguments. check input files\n\n",
	     m);
      exit( 1 );
    }
  } else {
    if ( m != garity[f->predicate] ) {
      printf("\npredicate %s is declared to have %d (not %d) arguments. check input files\n\n",
	     gpredicates[f->predicate],
	     garity[f->predicate], m);
      exit( 1 );
    }
  }
  /*
   * DEA - University of Brescia
   */
  }

  f->is_start_end_ovr = n->is_start_end_ovr;

  /*
   * End of DEA
   */

}



Bool is_subtype( int t1, int t2 )

{

  int i;

  for ( i = 0; i < gtype_size[t1]; i++ ) {
    if ( !gis_member[gtype_consts[t1][i]][t2] ) {
      return FALSE;
    }
  }

  return TRUE;

}



WffNode *make_Wff( PlNode *p, int num_vars )

{

  WffNode *tmp;
  int i;
  int t;
  PlNode *n;
  PlNode *num_prec;

  if ( !p ) {
    tmp = NULL;
    return tmp;
  }

  tmp = new_WffNode( p->connective );
  tmp->is_start_end_ovr = p->is_start_end_ovr;
  switch ( p->connective ) {
  case TIMED_FACT:
    tmp->value = p->value;
    tmp->sons = make_Wff(p->sons, num_vars);

    for ( n = p->sons->next; n; n = n->next ) {
      tmp->sons->prev = make_Wff( n, num_vars);
      tmp->sons->prev->next = tmp->sons;
      tmp->sons = tmp->sons->prev;
    }

    tmp->next = NULL;
    break;
  case ALL:
  case EX:
    for ( i = 0; i < num_vars; i++ ) {
      if ( lvar_names[i] == p->atom->item ||
	   strcmp( lvar_names[i], p->atom->item ) == SAME ) {
	printf("\nwarning: var quantification of %s overwrites previous declaration\n\n",
	       p->atom->item);
      }
    }
    if ( (t = position_in_types_table( p->atom->next->item)) == -1 ) {
      printf("\nwarning: quantified var %s has unknown or empty type %s. simplifying.\n\n",
	     p->atom->item, p->atom->next->item);
      tmp->connective = ( p->connective == EX ) ? FAL : TRU;
      break;
    }
    tmp->var = num_vars;
    tmp->var_type = t;
    tmp->var_name = new_Token( strlen( p->atom->item ) + 1 );
    strcpy( tmp->var_name, p->atom->item );
    lvar_names[num_vars] = p->atom->item;
    lvar_types[num_vars] = t;
    tmp->son = make_Wff( p->sons, num_vars + 1 );
    break;
  case AND:
  case OR:
    if ( !p->sons ) {
/*
 * DEA - University of Brescia
 */
      /* printf("\nwarning: empty con/disjunction in domain definition. simplifying.\n\n"); */
/*
 * End of DEA
 */
      tmp->connective = ( p->connective == OR ) ? FAL : TRU;
      break;
    }
    tmp->sons = make_Wff( p->sons, num_vars );
    for ( n = p->sons->next; n; n = n->next ) {
      tmp->sons->prev = make_Wff( n, num_vars );
      tmp->sons->prev->next = tmp->sons;
      tmp->sons = tmp->sons->prev;
    }
    break;
  case NOT:
    tmp->son = make_Wff( p->sons, num_vars );
    break;
  case ATOM:
    tmp->fact = new_Fact();
    make_Fact( tmp->fact, p, num_vars );
    
    /* Save predicates appearing in rules preconditions */
    if (save_rule_precond && (tmp->fact->predicate >= 0))
      SET_BIT(rules_precs[rule_num], tmp->fact->predicate);
  
    break;
  case TRU:
  case FAL:
    break;

    /*
     * DEA - University of Brescia
     */
   
    /*
     * Un nodo numerico non viene trasformato in WffNode. Verr� gestito in seguito
     **
     * Numeric nodes are not represented as WffNode. They will be translated later.
     */
  case BIN_COMP:
    num_prec = new_PlNode(BIN_COMP);
    num_prec->is_start_end_ovr = p->is_start_end_ovr;
    num_prec->sons = copy_PlNode(p->sons);
    num_prec->next = tmp->numeric;
    tmp->numeric = num_prec;
    break;

    /**
       I nodi OVERALL, AT_END, AT_START, e numerici (tranne le BIN_COMP) sono
       stati eliminati da reduce_pddl2_to_pddl1
     **/

    /*
  case AT_START_CONN:
  case AT_END_CONN:
  case OVER_ALL_CONN:
    //ignore pddl2 nfo about delayed effects or so
    free_WffNode (tmp);
    tmp = make_Wff (p->sons, num_vars);
    break;
  case F_EXP:
  case MUL_CONN:
  case DIV_CONN:
  case MINUS_CONN:
  case UMINUS_CONN:
  case PLUS_CONN:
  case LESS_THAN_CONN:
  case LESS_THAN_OR_EQUAL_CONN:
  case EQUAL_CONN:
  case GREATER_THAN_CONN:
  case GREATER_OR_EQUAL_CONN:
    tmp->sons = make_Wff (p->sons, num_vars);
      break;
  case FN_HEAD:
    tmp->numvar = new_NumVar ();
    make_NumVar (tmp->numvar, p, num_vars);
    break;
    */
/*
 * End of DEA
 */

  default:
    printf("\nforbidden connective %d in Pl Wff. must be a bug somewhere...\n\n",
	   p->connective);
    exit( 1 );
  }

  return tmp;

}



Effect *make_effect( PlNode *p, int num_vars )

{

  Effect *tmp = new_Effect();
  PlNode *n, *m;
  int t, i;

  for ( n = p; n && n->connective == ALL; n = n->sons ) {
    if ( (t = position_in_types_table( n->atom->next->item )) == -1 ) {
      printf("\nwarning: effect parameter %s has unknown or empty type %s. skipping effect.\n\n",
	     n->atom->item, n->atom->next->item);
      return NULL;
    }
    for ( i = 0; i < num_vars + tmp->num_vars; i++ ) {
      if ( lvar_names[i] == n->atom->item ||
	   strcmp( lvar_names[i], n->atom->item ) == SAME ) {
	printf("\nwarning: effect parameter %s overwrites previous declaration\n\n",
	       n->atom->item);
      }
    }
    lvar_types[num_vars + tmp->num_vars] = t;
    lvar_names[num_vars + tmp->num_vars] = n->atom->item;
    tmp->var_names[tmp->num_vars] = new_Token( strlen( n->atom->item ) + 1 );
    strcpy( tmp->var_names[tmp->num_vars], n->atom->item );
    tmp->var_types[tmp->num_vars++] = t;
  }

  if ( !n || n->connective != WHEN ) {
    printf("\nnon WHEN %d at end of effect parameters. debug me\n\n",
	   n->connective);
    print_PlNode(n, 1);
    exit( 1 );
  }

  tmp->conditions = make_Wff( n->sons, num_vars + tmp->num_vars );

  if ( n->sons->next->connective != AND ) {
    printf("\nnon AND %d in front of literal effect list. debug me\n\n",
	   n->sons->next->connective);
    exit( 1 );
  }
  if ( !n->sons->next->sons ) {
    return tmp;
  }
  m = n->sons->next->sons;
  tmp->effects = new_Literal();
  tmp->effects->is_start_end_ovr = m->is_start_end_ovr;
  if ( m->connective == NOT ) {
    tmp->effects->negated = TRUE;
    make_Fact( &(tmp->effects->fact), m->sons, num_vars + tmp->num_vars );
  } else {
    tmp->effects->negated = FALSE;
    make_Fact( &(tmp->effects->fact), m, num_vars + tmp->num_vars );
  }
  for ( m = m->next; m; m = m->next ) {
    tmp->effects->prev = new_Literal();
    tmp->effects->prev->is_start_end_ovr = m->is_start_end_ovr;
    if ( m->connective == NOT ) {
      tmp->effects->prev->negated = TRUE;
      make_Fact( &(tmp->effects->prev->fact), m->sons, num_vars + tmp->num_vars );
    } else {
      tmp->effects->prev->negated = FALSE;
      make_Fact( &(tmp->effects->prev->fact), m, num_vars + tmp->num_vars );
    }
    tmp->effects->prev->next = tmp->effects;
    tmp->effects = tmp->effects->prev;
  }

  return tmp;

}











/*************************
 * INERTIA PREPROCESSING *
 *************************/











void do_inertia_preprocessing_step_1( void )

{

  int i, j;
  Facts *f;

  collect_inertia_information();

  if ( gcmd_line.display_info == 105 ) {
    printf("\n\npredicates inertia info:");
    for ( i = 0; i < gnum_predicates; i++ ) {
      printf("\n%3d --> %s: ", i, gpredicates[i]);
      printf(" is %s, %s",
	     gis_added[i] ? "ADDED" : "NOT ADDED",
	     gis_deleted[i] ? "DELETED" : "NOT DELETED");
    }
    printf("\n\n");
  }

  split_initial_state();

  if ( gcmd_line.display_info == 106 ) {
    printf("\n\nsplitted initial state is:");
    printf("\nindividual predicates:");
    for ( i = 0; i < gnum_predicates; i++ ) {
      printf("\n\n%s:", gpredicates[i]);
      if ( !gis_added[i] &&
	   !gis_deleted[i] ) {
	printf(" ---  STATIC");
      }
      for ( j = 0; j < gnum_initial_predicate[i]; j++ ) {
	printf("\n");
	print_Fact( &(ginitial_predicate[i][j]) );
      }
    }
    printf("\n\nnon static part:");
    for ( f = ginitial; f; f = f->next ) {
      printf("\n");
      print_Fact( f->fact );
    }

    printf("\n\nextended types table:");
    for ( i = 0; i < gnum_types; i++ ) {
      printf("\n%d --> ", i);
      if ( gpredicate_to_type[i] == -1 ) {
	printf("%s ", gtype_names[i]);
      } else {
	printf("UNARY INERTIA TYPE (%s) ", gpredicates[gpredicate_to_type[i]]);
      }
      for ( j = 0; j < gtype_size[i]; j++ ) {
	printf("%d ", gtype_consts[i][j]);
      }
    }
  }

}



void collect_inertia_information( void )

{

  int i;
  Effect *e;
  Literal *l;

  for ( i = 0; i < gnum_predicates; i++ ) {
    gis_added[i] = FALSE;
    gis_deleted[i] = FALSE;
  }

  if (GpG.timed_facts_present)
    {
      WffNode *tmp, *t;

      for (tmp = timed_wff; tmp; tmp = tmp->next)
	{
	  for (t = tmp->sons; t; t = t->next)
	    {
	      if (t->connective == ATOM)
		{
		  gis_added[t->fact->predicate] = TRUE;
		}
	      else
		{
		  gis_deleted[t->son->fact->predicate] = TRUE;
		}
	    }
	}
    }

  for ( i = 0; i < gnum_operators; i++ ) {
    for ( e = goperators[i]->effects; e; e = e->next ) {
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  gis_deleted[l->fact.predicate] = TRUE;
	} else {
	  gis_added[l->fact.predicate] = TRUE;
	}
      }
    }
  }


  /*
   * DEA - University of Brescia
   */

  /* 
   * Analisi dei Predicati derivati
   **
   * Derived predicate analisys 
   */
  if (GpG.derived_predicates) {
    for ( i = 0; i < gnum_derived_predicates; i++ ) {
      for ( e = gderivedpred[i]->effects; e; e = e->next ) {
	for ( l = e->effects; l; l = l->next ) {
	  if ( l->negated ) {
	    gis_deleted[l->fact.predicate] = TRUE;
	  } else {
	    gis_added[l->fact.predicate] = TRUE;
	  }
	}
      }
    }
  }

  /*
   * End of DEA
   */
  

}



void split_initial_state( void )

{

  int i, j, p, t;
  Facts *tmp;
  token_list tok;

  for ( i = 0; i < MAX_PREDICATES; i++ ) {
    gtype_to_predicate[i] = -1;
  }
  for ( i = 0; i < MAX_TYPES; i++ ) {
    gpredicate_to_type[i] = -1;
  }

  for ( i = 0; i < gnum_predicates; i++ ) {
    if ( !gis_added[i] &&
	 !gis_deleted[i] &&
	 garity[i] == 1 ) {
      if ( gnum_types == MAX_TYPES ) {
	printf("\ntoo many (inferred) types! increase MAX_TYPES (currently %d)\n\n",
	       MAX_TYPES);
	exit( 1 );
      }
      gtype_to_predicate[i] = gnum_types;
      gpredicate_to_type[gnum_types] = i;
      gtype_names[gnum_types] = NULL;
      gtype_size[gnum_types] = 0;
      for ( j = 0; j < MAX_CONSTANTS; j++ ) {
	gis_member[j][gnum_types] = FALSE;
      }
      gnum_types++;
    }
  }
     

  /* double size of predicates table as each predicate might need
   * to be translated to NOT-p
   */
  ginitial_predicate = ( Fact ** ) calloc( gnum_predicates * 2, sizeof( Fact * ) );
  gnum_initial_predicate = ( int * ) calloc( gnum_predicates * 2, sizeof( int ) );
  for ( i = 0; i < gnum_predicates * 2; i++ ) {
    gnum_initial_predicate[i] = 0;
  }
  for ( i = 0; i < gnum_full_initial; i++ ) {
    p = gfull_initial[i].predicate;
    gnum_initial_predicate[p]++;
  }
  for ( i = 0; i < gnum_predicates; i++ ) {
    ginitial_predicate[i] = ( Fact * ) calloc( gnum_initial_predicate[i], sizeof( Fact ) );
    gnum_initial_predicate[i] = 0;
  }
  ginitial = NULL;
  gnum_initial = 0;

  for ( i = 0; i < gnum_full_initial; i++ ) {
    p = gfull_initial[i].predicate;
    ginitial_predicate[p][gnum_initial_predicate[p]].predicate = p;
    for ( j = 0; j < garity[p]; j++ ) {
      ginitial_predicate[p][gnum_initial_predicate[p]].args[j] = gfull_initial[i].args[j];
    }
    gnum_initial_predicate[p]++;
    if ( gis_added[p] ||
	 gis_deleted[p] ) {
      tmp = new_Facts();
      tmp->fact->predicate = p;
      for ( j = 0; j < garity[p]; j++ ) {
	tmp->fact->args[j] = gfull_initial[i].args[j];
      }
      tmp->next = ginitial;
      ginitial = tmp;
      gnum_initial++;
    } else {
      /* Fatto inerziale */
      sprintf(temp_name, "(%s", gpredicates[p]);
      for (j = 0; j < garity[p]; j++)
	{
	  sprintf(&temp_name[strlen(temp_name)], " %s", gconstants[gfull_initial[i].args[j]]);
	}
      sprintf(&temp_name[strlen(temp_name)], ") ");

      tok = ( token_list_elt *) malloc(sizeof( token_list_elt ));
      tok->item=NULL;
      tok->index=-1;
      tok->item = (char *) calloc ( strlen(temp_name)+1, sizeof(char) );
      strcpy( tok->item, temp_name);
 
      tok->next = inertial_facts;
      inertial_facts = tok;

        if ( garity[p] == 1 ) {
	t = gtype_to_predicate[p];
	if ( gtype_size[t] == MAX_TYPE ) {
	  printf("\ntoo many consts in type %s! increase MAX_TYPE (currently %d)\n\n",
		 gtype_names[t], MAX_TYPE);
	  exit( 1 );
	}
	if ( !gis_member[gfull_initial[i].args[0]][gpredicates_args_type[p][0]] ) {
	  printf("\ntype mismatch in initial state! %s as arg 0 of %s\n\n",
		 gconstants[gfull_initial[i].args[0]], gpredicates[p]);
	  exit( 1 );
	}
	gtype_consts[t][gtype_size[t]++] = gfull_initial[i].args[0];
	gis_member[gfull_initial[i].args[0]][t] = TRUE;
      }
    }
  }

}











/******************************
 * NORMALIZE ALL PL1 FORMULAE *
 ******************************/












void normalize_all_wffs( void )

{

  int i;
  Effect *e;

  simplify_wff( &ggoal );
  remove_unused_vars_in_wff( &ggoal );
  expand_quantifiers_in_wff( &ggoal, NULL, -1, -1 );
  NOTs_down_in_wff( &ggoal );
  cleanup_wff( &ggoal );

  /*
   * DEA - University of Brescia
   */

  if (FALSE)

  /*
   * End of DEA
   */

  if ( ggoal->connective == TRU ) {
    printf("\nff: goal can be simplified to TRUE. The empty plan solves it\n\n");
    exit( 1 );
  }
  if (ggoal->connective == FAL ) {
    printf("\nff: goal can be simplified to FALSE. No plan will solve it\n\n");
    exit( 1 );
  }
  /* put goal into DNF right away: fully instantiated already
   */
  dnf( &ggoal );
  cleanup_wff( &ggoal );
  
  for ( i = 0; i < gnum_operators; i++ ) {

    add_implicit_preconds(goperators[i]);

    if (goperators[i] -> preconds) {
      simplify_wff( &(goperators[i]->preconds) );
      remove_unused_vars_in_wff( &(goperators[i]->preconds) );
      expand_quantifiers_in_wff( &(goperators[i]->preconds), NULL, -1, -1 );
      NOTs_down_in_wff( &(goperators[i]->preconds) );
      cleanup_wff( &(goperators[i]->preconds) );
      
      for ( e = goperators[i]->effects; e; e = e->next ) {
	simplify_wff( &(e->conditions) );
	remove_unused_vars_in_wff( &(e->conditions) );
	expand_quantifiers_in_wff( &(e->conditions), NULL, -1, -1 );
	NOTs_down_in_wff( &(e->conditions) );
	cleanup_wff( &(e->conditions) );
      }
    }
  }

  /* Predicati derivati IFDEF */
  if (GpG.derived_predicates) {
    for (i = 0; i < gnum_derived_predicates; i++) {

      add_implicit_preconds(gderivedpred[i]);

      if (gderivedpred[i] -> preconds) {
	simplify_wff(&(gderivedpred[i]->preconds));
	remove_unused_vars_in_wff(&(gderivedpred[i]->preconds));
	expand_quantifiers_in_wff(&(gderivedpred[i]->preconds), NULL, -1, -1);
	NOTs_down_in_wff(&(gderivedpred[i]->preconds));
	cleanup_wff(&(gderivedpred[i]->preconds));
	
	for (e = gderivedpred[i]->effects; e; e = e->next) {
	  simplify_wff( &(e->conditions) );
	  remove_unused_vars_in_wff( &(e->conditions) );
	  expand_quantifiers_in_wff( &(e->conditions), NULL, -1, -1 );
	  NOTs_down_in_wff( &(e->conditions) );
	  cleanup_wff( &(e->conditions) );
	}
      }
    }
  }
  /* ENDIF */

  if ( gcmd_line.display_info == 107 ) {
    printf("\n\ndomain with normalized PL1 formula:");

    printf("\n\noperators are:");
    for ( i = 0; i < gnum_operators; i++ ) {
      print_Operator( goperators[i] );
    }
    printf("\n\n");

    printf("\n\ngoal is:\n");
    print_Wff( ggoal, 0 );
  }

}



void remove_unused_vars_in_wff( WffNode **w )

{

  WffNode *tmp;
  WffNode *i;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    remove_unused_vars_in_wff( &((*w)->son) );
    if ( !var_used_in_wff( ENCODE_VAR( (*w)->var ), (*w)->son ) ) {
      decrement_inferior_vars((*w)->var, (*w)->son );
      (*w)->connective = (*w)->son->connective;
      (*w)->var = (*w)->son->var;
      (*w)->var_type = (*w)->son->var_type;
      if ( (*w)->var_name ) {
	free( (*w)->var_name );
      }
      (*w)->var_name = (*w)->son->var_name;
      (*w)->sons = (*w)->son->sons;
      if ( (*w)->fact ) {
	free( (*w)->fact );
      }
      (*w)->fact = (*w)->son->fact;
      tmp = (*w)->son;
      (*w)->son = (*w)->son->son;
      free( tmp );
    }
    break;
  case AND:
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      remove_unused_vars_in_wff( &i );
    }
    break;
  case NOT:
    remove_unused_vars_in_wff( &((*w)->son) );
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: remove var, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}



Bool var_used_in_wff( int code_var, WffNode *w )

{

  WffNode *i;
  int j;

  switch ( w->connective ) {
  case ALL:
  case EX:
    return var_used_in_wff( code_var, w->son );
  case AND:
  case OR:
    for ( i = w->sons; i; i = i->next ) {
      if ( var_used_in_wff( code_var, i ) ) {
	return TRUE;
      }
    }
    return FALSE;
  case NOT:
    return var_used_in_wff( code_var, w->son );
  case ATOM:
    if ( w->fact->predicate == -1 ) {
      if ( w->fact->args[0] == code_var ) {
	return TRUE;
      }
      if ( w->fact->args[1] == code_var ) {
	return TRUE;
      }
      return FALSE;
    }
    for ( j = 0; j < garity[w->fact->predicate]; j++ ) {
      if ( w->fact->args[j] >= 0 ) {
	continue;
      }
      if ( w->fact->args[j] == code_var ) {
	return TRUE;
      }
    }
    return FALSE;
  case TRU:
  case FAL:
  case BIN_COMP:
    return TRUE;
  default:
    printf("\nwon't get here: var used ?, non logical %d\n\n",
	   w->connective);
    exit( 1 );
  }
}



void decrement_inferior_vars( int var, WffNode *w )

{

  WffNode *i;
  int j;

  switch ( w->connective ) {
  case ALL:
  case EX:
    w->var--;
    decrement_inferior_vars( var, w->son );
    break;
  case AND:
  case OR:
    for ( i = w->sons; i; i = i->next ) {
      decrement_inferior_vars( var, i );
    }
    break;
  case NOT:
    decrement_inferior_vars( var, w->son );
    break;
  case ATOM:
    if ( w->fact->predicate == -1 ) {
      if ( w->fact->args[0] < 0 &&
	   DECODE_VAR( w->fact->args[0] ) > var ) {
	w->fact->args[0]++;
      }
      if ( w->fact->args[1] < 0 &&
	   DECODE_VAR( w->fact->args[1] ) > var ) {
	w->fact->args[1]++;
      }
      break;
    }
    for ( j = 0; j < garity[w->fact->predicate]; j++ ) {
      if ( w->fact->args[j] >= 0 ) {
	continue;
      }
      if ( DECODE_VAR( w->fact->args[j] ) > var ) {
	w->fact->args[j]++;
      }
    }
    break;
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: decrement, non logical %d\n\n",
	   w->connective);
    exit( 1 );
  }

}



void simplify_wff( WffNode **w )

{

  WffNode *i, *tmp;
  int m;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    simplify_wff( &((*w)->son) );
    if ( (*w)->son->connective == TRU ||
	 (*w)->son->connective == FAL ) {
      (*w)->connective = (*w)->son->connective;
      free( (*w)->son );
      (*w)->son = NULL;
      if ( (*w)->var_name ) {
	free( (*w)->var_name );
      }
    }
    break;
  case AND:
    m = 0;
    i = (*w)->sons;
    while ( i ) {
      simplify_wff( &i );
      if ( i->connective == FAL ) {
	(*w)->connective = FAL;
	free_WffNode( (*w)->sons );
	(*w)->sons = NULL;
	return;
      }
      if ( i->connective == TRU ) {
	if ( i->prev ) {
	  i->prev->next = i->next;
	} else {
	  (*w)->sons = i->next;
	}
	if ( i->next ) {
	  i->next->prev = i->prev;
	}
	tmp = i;
	i = i->next;
	free( tmp );
	continue;
      }
      i = i->next;
      m++;
    }
    if ( m == 0 ) {
      (*w)->connective = TRU;
      free_WffNode( (*w)->sons );
      (*w)->sons = NULL;
    }
    if ( m == 1 ) {
      (*w)->connective = (*w)->sons->connective;
      (*w)->var = (*w)->sons->var;
      (*w)->var_type = (*w)->sons->var_type;
      if ( (*w)->var_name ) {
	free( (*w)->var_name );
      }
      (*w)->numeric = (*w)->sons->numeric;
      (*w)->sons->numeric = NULL;
      (*w)->var_name = (*w)->sons->var_name;
      (*w)->son = (*w)->sons->son;
      if ( (*w)->fact ) {
	free( (*w)->fact );
      }
      (*w)->fact = (*w)->sons->fact;
      tmp = (*w)->sons;
      (*w)->sons = (*w)->sons->sons;
      free( tmp );
    }
    break;
  case OR:
    m = 0;
    i = (*w)->sons;
    while ( i ) {
      simplify_wff( &i );
      if ( i->connective == TRU ) {
	(*w)->connective = TRU;
	free_WffNode( (*w)->sons );
	(*w)->sons = NULL;
	return;
      }
      if ( i->connective == FAL ) {
	if ( i->prev ) {
	  i->prev->next = i->next;
	} else {
	  (*w)->sons = i->next;
	}
	if ( i->next ) {
	  i->next->prev = i->prev;
	}
	tmp = i;
	i = i->next;
	free( tmp );
	continue;
      }
      i = i->next;
      m++;
    }
    if ( m == 0 ) {
      (*w)->connective = FAL;
      free_WffNode( (*w)->sons );
      (*w)->sons = NULL;
    }
    if ( m == 1 ) {
      (*w)->connective = (*w)->sons->connective;
      (*w)->var = (*w)->sons->var;
      (*w)->var_type = (*w)->sons->var_type;
      if ( (*w)->var_name ) {
	free( (*w)->var_name );
      }
      (*w)->numeric = (*w)->sons->numeric;
      (*w)->sons->numeric = NULL;
      (*w)->var_name = (*w)->sons->var_name;
      (*w)->son = (*w)->sons->son;
      if ( (*w)->fact ) {
	free( (*w)->fact );
      }
      (*w)->fact = (*w)->sons->fact;
      tmp = (*w)->sons;
      (*w)->sons = (*w)->sons->sons;
      free( tmp );
    }
    break;
  case NOT:
    simplify_wff( &((*w)->son) );
    if ( (*w)->son->connective == TRU ||
	 (*w)->son->connective == FAL ) {
      (*w)->connective = ( (*w)->son->connective == TRU ) ? FAL : TRU;
      free( (*w)->son );
      (*w)->son = NULL;
    }
    break;
  case ATOM:
    if ( (*w)->visited ) {
      /* already seen and not changed
       */
      break;
    }
    if ( (*w)->fact->predicate == -1 ) {
      if ( (*w)->fact->args[0] == (*w)->fact->args[1] ) {
	(*w)->connective = TRU;
	free( (*w)->fact );
	(*w)->fact = NULL;
	break;
      }
      if ( (*w)->fact->args[0] > -1 &&
	   (*w)->fact->args[1] > -1 &&
	   (*w)->fact->args[0] != (*w)->fact->args[1] ) {
      	(*w)->connective = FAL;
	free( (*w)->fact );
	(*w)->fact = NULL;
	break;
      }
      break;
    }
    if ( !possibly_negative( (*w)->fact ) ) {
      (*w)->connective = TRU;
      free( (*w)->fact );
      (*w)->fact = NULL;
      break;
    }
    if ( !possibly_positive( (*w)->fact ) ) {
      (*w)->connective = FAL;
      free( (*w)->fact );
      (*w)->fact = NULL;
      break;
    }
    (*w)->visited = TRUE;
    break;
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: simplify, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}


/*
 * DEA - University of Brescia
 */

/**
 * Sostituisce tutte le occorrenze della variabile "var_name "con una costante "costant" all'interno del PlNode p;
 **
 * Replace all the occurence of a variable "var_name" with "costant"  the PlNode p.
 **/
void replace_var_with_const(char *var_name, int constant, PlNode *p)
{
  TokenList *tl;
  PlNode *tmp;

  switch (p->connective)
    {
    case FN_HEAD:
    case FN_ATOM:
    case ATOM: 
      for (tl = p->atom; tl; tl = tl->next)
	{
	  if (strcmp(tl->item, var_name) == SAME)
	    strcpy(tl->item, gconstants[constant]);
	}
      break;
    case BIN_COMP:
    case MINIMIZE_CONN:
    case MAXIMIZE_CONN:
    case METRIC_CONN:
    case INCREASE_CONN:
    case DECREASE_CONN:
    case SCALE_UP_CONN:
    case SCALE_DOWN_CONN:
    case LESS_THAN_CONN:
    case LESS_THAN_OR_EQUAL_CONN:
    case EQUAL_CONN:
    case GREATER_THAN_CONN:
    case GREATER_OR_EQUAL_CONN:
    case MUL_CONN:
    case DIV_CONN:
    case PLUS_CONN:
    case NUM_EXP:
    case F_EXP:
    case F_EXP_T:
    case AND:
    case OR:
    case NOT:
      for (tmp = p->sons; tmp; tmp = p->next)
	replace_var_with_const(var_name, constant, tmp);
      break;
    case TRU:
    case FAL:
      break;
    default:
      break;
    }
}

/*
 * End of DEA
 */

void expand_quantifiers_in_wff( WffNode **w, char *var_name, int var, int constant )

{

  WffNode *r = NULL, *tmp, *i;
  int j, l;
  Bool change;
  VarList *inst_var;

  if ( !(*w) ) {
    return;
  }

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    if ( var != -1 ) {/* depth first: upper node is active */
      expand_quantifiers_in_wff( &((*w)->son), var_name, var, constant );
      return;
    }

    (*w)->connective = ( (*w)->connective == ALL ) ? AND : OR;
    for ( j = 0; j < gtype_size[(*w)->var_type]; j++ ) {
      tmp = copy_Wff( (*w)->son );
      expand_quantifiers_in_wff( &tmp, (*w)->var_name, (*w)->var, gtype_consts[(*w)->var_type][j] );
      tmp->next = r;
      if ( r ) {
	r->prev = tmp;
      }
      r = tmp;
    }

    free_WffNode( (*w)->son );
    (*w)->son = NULL;
    (*w)->sons = r;
    (*w)->var = -1;
    (*w)->var_type = -1;
    if ( (*w)->var_name ) {
      free( (*w)->var_name );
    }
    (*w)->var_name = NULL;

    /* now make all sons expand their quantifiers
     */
    for ( i = (*w)->sons; i; i = i->next ) {
      expand_quantifiers_in_wff( &i, NULL, -1, -1 );
    }
    break;
  case AND:
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      expand_quantifiers_in_wff( &i, var_name, var, constant );
    }
    break;
  case NOT:
    expand_quantifiers_in_wff( &((*w)->son), var_name, var, constant );
    break;
  case ATOM:
    if ( var == -1 ) {
      break;
    }

    if ( (*w)->fact->predicate == -1 ) {
      if ( (*w)->fact->args[0] == ENCODE_VAR( var ) ) {
	(*w)->fact->args[0] = constant;
      }
      if ( (*w)->fact->args[1] == ENCODE_VAR( var ) ) {
	(*w)->fact->args[1] = constant;
      }
      if ( (*w)->fact->args[0] == (*w)->fact->args[1] ) {
	(*w)->connective = TRU;
	free( (*w)->fact );
	(*w)->fact = NULL;
	break;
      }
      if ( (*w)->fact->args[0] > -1 &&
	   (*w)->fact->args[1] > -1 &&
	   (*w)->fact->args[0] != (*w)->fact->args[1] ) {
      	(*w)->connective = FAL;
	free( (*w)->fact );
	(*w)->fact = NULL;
	break;
      }
      break;
    }

    change = FALSE;
    for ( l = 0; l < garity[(*w)->fact->predicate]; l++ ) {
      if ( (*w)->fact->args[l] == ENCODE_VAR( var ) ) {
	(*w)->fact->args[l] = constant;
	change = TRUE;
      }
    }
    if ( !change && (*w)->visited ) {
      /* we did not change anything and we've already seen that node
       * --> it cant be simplified
       */
      break;
    }
    if ( !possibly_negative( (*w)->fact ) ) {
      (*w)->connective = TRU;
      free( (*w)->fact );
      (*w)->fact = NULL;
      break;
    }
    if ( !possibly_positive( (*w)->fact ) ) {
      (*w)->connective = FAL;
      free( (*w)->fact );
      (*w)->fact = NULL;
      break;
    }
    (*w)->visited = TRUE;
    break;
  case TRU:
  case FAL:
    break;
    /*
     * DEA - University of Brescia
     */
    
    /**
     * Espando i nodi numerici: sostituisco la variabile da espandere con 
     * la costante considerata in questo passo e salvo l'associazione nella
     * lista instantiated_vars
     **
     * Expand numeric nodes: replace the quantified variable with the actual
     * constant and save the association (variable, constant) in the list
     * instantiated_vars
     */
  case BIN_COMP:
    if (!var_name)
      break;
    inst_var = new_VarList(var_name, constant);
    inst_var->next = (*w)->instantiated_vars;
    replace_var_with_const(var_name, constant, (*w)->numeric);
    (*w)->instantiated_vars = inst_var;
    (*w)->visited = TRUE;
    break;

    /*
     * End of DEA
     */

  default:
    printf("\nwon't get here: expansion, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}



WffNode *copy_Wff( WffNode *w )

{

  WffNode *tmp, *tmp2, *i;
  int j;

  tmp = new_WffNode( w->connective );
  tmp->is_start_end_ovr = w->is_start_end_ovr;

  switch ( w->connective ) {
  case ALL:
  case EX:
    tmp->var = w->var;
    tmp->var_name = copy_Token(w->var_name);
    tmp->var_type = w->var_type;
    tmp->son = copy_Wff( w->son );
    break;
  case AND:
  case OR:
    for ( i = w->sons; i; i = i->next ) {
      tmp2 = copy_Wff( i );
      if ( tmp->sons ) {
	tmp->sons->prev = tmp2;
      }
      tmp2->next = tmp->sons;
      tmp->sons = tmp2;
    }
    break;
  case NOT:
    tmp->son = copy_Wff( w->son );
    break;
  case ATOM:
    tmp->fact = new_Fact();
    tmp->fact->predicate = w->fact->predicate;
    tmp->fact->added_implicit = w->fact->added_implicit;
    if ( w->fact->predicate == -1 ) {
      for ( j = 0; j < 2; j++ ) {
	tmp->fact->args[j] = w->fact->args[j];
      }
    } else {
      for ( j = 0; j < garity[w->fact->predicate]; j++ ) {
	tmp->fact->args[j] = w->fact->args[j];
      }
    } 
    tmp->visited = w->visited;
    break;
  case BIN_COMP:
    tmp->numeric = copy_PlNode(w->numeric);
    tmp->instantiated_vars = copy_VarList(w->instantiated_vars);
    tmp->visited = w->visited;
    break;
  case TRU:
  case FAL:
    break;
  default:
    printf("\nwon't get here: copy, non logical %d\n\n",
	   w->connective);
    exit( 1 );
  }

  return tmp;

}



Bool possibly_positive( Fact *f )

{

  int i;

  if ( gis_added[f->predicate] ) {
    return TRUE;
  }

  for ( i = 0; i < gnum_initial_predicate[f->predicate]; i++ ) {
    if ( matches( f, &(ginitial_predicate[f->predicate][i]) ) ) {
      return TRUE;
    }
  }

  return FALSE;

}



Bool possibly_negative( Fact *f )

{

  int i;

  if ( gis_deleted[f->predicate] ) {
    return TRUE;
  }

  for ( i = 0; i < garity[f->predicate]; i++ ) {
    if ( f->args[i] < 0 ) {
      return TRUE;
    }
  }

  for ( i = 0; i < gnum_initial_predicate[f->predicate]; i++ ) {
    if ( matches( f, &(ginitial_predicate[f->predicate][i]) ) ) {
      return FALSE;
    }
  }

  return TRUE;

}



Bool matches( Fact *f1, Fact *f2 )

{

  int i;

  for ( i = 0; i < garity[f1->predicate]; i++ ) {
    if ( f1->args[i] >= 0 ) {
      if ( f2->args[i] >= 0 &&
	   f1->args[i] != f2->args[i] ) {
	return FALSE;
      }
    }
  }

  return TRUE;

}



void cleanup_wff( WffNode **w )

{

  merge_ANDs_and_ORs_in_wff( w );
  detect_tautologies_in_wff( w );
  simplify_wff( w );
  detect_tautologies_in_wff( w );
  merge_ANDs_and_ORs_in_wff( w );

}



void detect_tautologies_in_wff( WffNode **w )

{

  WffNode *i, *j, *tmp;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    detect_tautologies_in_wff( &((*w)->son) );
    break;
  case AND:
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      detect_tautologies_in_wff( &i );
    }
    for ( i = (*w)->sons; i && i->next; i = i->next ) {
      j = i->next;
      while ( j ) {
	if ( are_identical_ATOMs( i, j ) ) {
	  j->prev->next = j->next;
	  if ( j->next ) {
	    j->next->prev = j->prev;
	  }
	  tmp = j;
	  j = j->next;
	  if ( tmp->fact ) {
	    free( tmp->fact );
	  }
	  free( tmp );
	  continue;
	}
	if ( i->connective == NOT &&
	     are_identical_ATOMs( i->son, j ) ) {
	  (*w)->connective = ( (*w)->connective == AND ) ? FAL : TRU;
	  free_WffNode( (*w)->son );
	  (*w)->son = NULL;
	  return;
	}
	if ( j->connective == NOT &&
	     are_identical_ATOMs( i, j->son ) ) {
	  (*w)->connective = ( (*w)->connective == AND ) ? FAL : TRU;
	  free_WffNode( (*w)->son );
	  (*w)->son = NULL;
	  return;
	}
	j = j->next;
      }
    }
    break;
  case NOT:
    detect_tautologies_in_wff( &((*w)->son) );
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: tautologies, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}



Bool are_identical_ATOMs( WffNode *w1, WffNode *w2 )

{

  int i;
  // static j=0;

  if ( w1->connective != ATOM ||
       w2->connective != ATOM ) {
    return FALSE;
  }

  if (w1->is_start_end_ovr != w2->is_start_end_ovr)
    return FALSE;

  if ( w1->fact->predicate != w2->fact->predicate ) {
    return FALSE;
  }

  for ( i = 0; i < ((w1->fact->predicate < 0)? 2 : garity[w1->fact->predicate]); i++ ) {
    //  j++;
    if ( w1->fact->args[i] != w2->fact->args[i] ) {
      return FALSE;
    }
  }

  return TRUE;

}



void merge_ANDs_and_ORs_in_wff( WffNode **w )

{

  WffNode *i, *j, *tmp;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    merge_ANDs_and_ORs_in_wff( &((*w)->son) );
    break;
  case AND:
  case OR:
    i = (*w)->sons;
    while ( i ) {
      merge_ANDs_and_ORs_in_wff( &i );
      if ( i->connective == (*w)->connective ) {
	if ( !(i->sons) ) {
	  if ( i->next ) {
	    i->next->prev = i->prev;
	  }
	  if ( i->prev ) {
	    i->prev->next = i->next;
	  } else {
	    (*w)->sons = i->next;
	  }
	  tmp = i;
	  i = i->next;
	  free( tmp );
	  continue;
	}
	for ( j = i->sons; j->next; j = j->next );
	j->next = i->next;
	if ( i->next ) {
	  i->next->prev = j;
	}
	if ( i->prev ) {
	  i->prev->next = i->sons;
	  i->sons->prev = i->prev;
	} else {
	  (*w)->sons = i->sons;
	}
	tmp = i;
	i = i->next;
	free( tmp );
	continue;
      }
      i = i->next;
    }
    break;
  case NOT:
    merge_ANDs_and_ORs_in_wff( &((*w)->son) );
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: merge, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}


/*
 * DEA - University od Brescia
 */

/**
 * Inverte una precondizione numerica rappresentata dal PlNode p. Viene
 * Utilizzata per eliminare le negazioni nelle precondizioni numeriche di
 * un operatore.
 **
 * Reverse a numeric condition represented by the PlNode p. This function is
 * used to replace a negative numeric condition with a positive one in operators.
 **/

void reverse_numeric_condition(PlNode *p)
{

  if (p->connective != BIN_COMP)
    return;

  switch (p->sons->connective)
    {
    case LESS_THAN_CONN:
      p->sons->connective = GREATER_OR_EQUAL_CONN;
      break;
    case LESS_THAN_OR_EQUAL_CONN:
      p->sons->connective = GREATER_THAN_CONN;
      break;
    case EQUAL_CONN:
      printf("\n\nWarning: numeric NOT EQUAL found in action preconditions. Not handled yet.");
      break;
    case  GREATER_THAN_CONN:
      p->sons->connective = LESS_THAN_OR_EQUAL_CONN;
      break;
    case GREATER_OR_EQUAL_CONN:
      p->sons->connective = LESS_THAN_CONN;
      break;
    default:
      printf("\n\nError: Invalid numeric action precondition.");
      exit(1);
    }
  
}

/*
 * End of DEA
 */


void NOTs_down_in_wff( WffNode **w )

{

  WffNode *tmp1, *tmp2, *i;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    printf("\ntrying to put nots down in quantified formula! debug me\n\n");
    exit( 1 );
    break;
  case AND:
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      NOTs_down_in_wff( &i ); 
    }
    break;
  case NOT:
    if ( (*w)->son->connective == BIN_COMP)
      {
	(*w)->connective = BIN_COMP;
	reverse_numeric_condition((*w)->numeric);
	free_WffNode((*w)->son);
	(*w)->son = NULL;
	break;
      }
    if ( (*w)->son->connective == NOT ) {
      (*w)->connective = (*w)->son->son->connective;
      (*w)->fact = (*w)->son->son->fact;
      tmp1 = (*w)->son;
      tmp2 = (*w)->son->son;
      (*w)->son = (*w)->son->son->son;
      free( tmp1 );
      free( tmp2 );
      NOTs_down_in_wff( w );
      break;
    }
    if ( (*w)->son->connective == AND ||
	 (*w)->son->connective == OR ) {
      (*w)->connective = ( (*w)->son->connective == AND ) ? OR : AND;
      (*w)->sons = (*w)->son->sons;
      free( (*w)->son );
      (*w)->son = NULL;
      for ( i = (*w)->sons; i; i = i->next ) {
	tmp1 = new_WffNode( i->connective );
	tmp1->is_start_end_ovr = i->is_start_end_ovr;
	tmp1->son = i->son;
	tmp1->sons = i->sons;
	tmp1->fact = i->fact;
	i->connective = NOT;
	i->son = tmp1;
	i->sons = NULL;
	i->fact = NULL;
	NOTs_down_in_wff( &i );
      }
      break;
    }
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: nots down, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }


}











/****************************************************
 * NEGATIVE PRE- AND EFFECT- CONDITIONS TRANSLATION *
 ****************************************************/








int lconsts[MAX_ARITY];








void translate_negative_preconds( void )

{

  int i, j;
  Effect *e;
  Facts *f;

  while ( translate_one_negative_cond( ggoal ) );
  
  for ( i = 0; i < gnum_operators; i++ ) {
    while ( translate_one_negative_cond( goperators[i]->preconds ) );

    for ( e = goperators[i]->effects; e; e = e->next ) {
      while ( translate_one_negative_cond( e->conditions ) );
    }
  }

  /* Predicati derivati IFDEF */
  if (GpG.derived_predicates) {
    for ( i = 0; i < gnum_derived_predicates; i++ ) {
      while ( translate_one_negative_cond( gderivedpred[i]->preconds ) );
      
      for ( e = gderivedpred[i]->effects; e; e = e->next ) {
	while ( translate_one_negative_cond( e->conditions ) );
      }
    }
  }
  /* ENDIF */

  if ( gcmd_line.display_info == 108 ) {
    printf("\n\ndomain with translated negative conds:");

    printf("\n\noperators are:");
    for ( i = 0; i < gnum_operators; i++ ) {
      print_Operator( goperators[i] );
    }
    printf("\n\n");

    printf("\ninitial state is:\n");
    for ( f = ginitial; f; f = f->next ) {
      printf("\n");
      print_Fact( f->fact );
    }
    printf("\n\n");

    printf("\n\nindividual predicates:\n");
    for ( i = 0; i < gnum_predicates; i++ ) {
      printf("\n\n%s:", gpredicates[i]);
      if ( !gis_added[i] &&
	   !gis_deleted[i] ) {
	printf(" ---  STATIC");
      }
      for ( j = 0; j < gnum_initial_predicate[i]; j++ ) {
	printf("\n");
	print_Fact( &(ginitial_predicate[i][j]) );
      }
    }
    printf("\n\n");

    printf("\n\ngoal is:\n");
    print_Wff( ggoal, 0 );
    printf("\n\n");
  }

}



Bool translate_one_negative_cond( WffNode *w )

{

  WffNode *i;
  int p, j, k, m;
  char *new_pred;
  Effect *e;
  Literal *l, *tmp;

  switch ( w->connective ) {
  case ALL:
  case EX:
    printf("\ntranslating NOT in quantified formula! debug me\n\n");
    exit( 1 );
  case AND:
  case OR:
    for ( i = w->sons; i; i = i->next ) {
      if ( translate_one_negative_cond( i ) ) {
	return TRUE;
      }
    }
    return FALSE;
  case NOT:
    if ( w->son->fact->predicate == -1 ) {
      return FALSE;
    }
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    return FALSE;
  default:
    printf("\nwon't get here: remove var, non logical %d\n\n",
	   w->connective);
    exit( 1 );
  }


  if ( gnum_predicates == MAX_PREDICATES ) {
    printf("\ntoo many predicates in translation! increase MAX_PREDICATES (currently %d)\n\n",
	   MAX_PREDICATES);
    exit( 1 );
  }

  p = w->son->fact->predicate;
  new_pred = new_Token( strlen( gpredicates[p] ) + 5 );
  sprintf( new_pred, "%s%s", STR_NOT_MINUS, gpredicates[p] );

  gpredicates_type[gnum_predicates] = gpredicates_type[p];
  garity[gnum_predicates] = garity[p];
 
  for ( j = 0; j < garity[p]; j++ ) {
    gpredicates_args_type[gnum_predicates][j] = 
      gpredicates_args_type[p][j];
  }
  gis_added[gnum_predicates] = FALSE;
  gis_deleted[gnum_predicates] = FALSE;
  m = 1;
  for ( j = 0; j < garity[gnum_predicates]; j++ ) {
    m *= gtype_size[gpredicates_args_type[gnum_predicates][j]];
  }
  ginitial_predicate[gnum_predicates] = ( Fact * ) calloc( m, sizeof( Fact ) );

  gpredicates[gnum_predicates] = new_pred;
 
  gnum_predicates++;
  
  replace_not_p_with_n_in_wff( p, gnum_predicates - 1, &ggoal );
  
  if (GpG.timed_facts_present)
    {   
      for (i = timed_wff; i != NULL; i = i->next)
        replace_not_p_with_n_in_wff(p, gnum_predicates - 1, &i);
    }

  for ( j = 0; j < gnum_operators; j++ ) {
    replace_not_p_with_n_in_wff( p, gnum_predicates - 1, &(goperators[j]->preconds) );

    for ( e = goperators[j]->effects; e; e = e->next ) {
      replace_not_p_with_n_in_wff( p, gnum_predicates - 1, &(e->conditions) );
      for ( l = e->effects; l; l = l->next ) {
	if ( l->fact.predicate != p ) {
	  continue;
	}
	tmp = new_Literal();
	if ( l->negated ) {
	  tmp->negated = FALSE;
	  gis_added[gnum_predicates - 1] = TRUE;
	} else {
	  tmp->negated = TRUE;
	  gis_deleted[gnum_predicates - 1] = TRUE;
	}
	tmp->fact.predicate = gnum_predicates - 1;
	for ( k = 0; k < garity[p]; k++ ) {
	  tmp->fact.args[k] = l->fact.args[k];
	  }
	if ( l->prev ) {
	  tmp->prev = l->prev;
	  tmp->prev->next = tmp;
	} else {
	  e->effects = tmp;
	}
	tmp->next = l;
	l->prev = tmp;
      }
    }
  }

  /*
   * DEA - University of Brescia
   */

  /* 
   * Analisi dei Predicati derivati
   **
   * Derived predicate analisys 
   */
  if (GpG.derived_predicates) {
    for ( j = 0; j < gnum_derived_predicates; j++ ) {
      replace_not_p_with_n_in_wff( p, gnum_predicates - 1, 
		      &(gderivedpred[j]->preconds) );
      
      for ( e = gderivedpred[j]->effects; e; e = e->next ) {
	replace_not_p_with_n_in_wff( p, gnum_predicates - 1, 
				&(e->conditions) );
	for ( l = e->effects; l; l = l->next ) {
	  if ( l->fact.predicate != p ) {
	    continue;
	  }
	  tmp = new_Literal();
	  if ( l->negated ) {
	    tmp->negated = FALSE;
	    gis_added[gnum_predicates - 1] = TRUE;
	  } else {
	    tmp->negated = TRUE;
	    gis_deleted[gnum_predicates - 1] = TRUE;
	  }
	  tmp->fact.predicate = gnum_predicates - 1;
	  for ( k = 0; k < garity[p]; k++ ) {
	    tmp->fact.args[k] = l->fact.args[k];
	  }
	  if ( l->prev ) {
	    tmp->prev = l->prev;
	    tmp->prev->next = tmp;
	  } else {
	    e->effects = tmp;
	  }
	  tmp->next = l;
	  l->prev = tmp;
	}
      }
    }
  }
 /*
  * End of DEA 
  */ 

  add_to_initial_state( p, gnum_predicates - 1, 0 );

  return TRUE;

}



void replace_not_p_with_n_in_wff( int p, int n, WffNode **w )

{

  WffNode *i;

  switch ( (*w)->connective ) {
  case TIMED_FACT:
    for ( i = (*w)->sons; i; i = i->next ) {
      replace_not_p_with_n_in_wff( p, n, &i );
    }
    break;
  case ALL:
  case EX:
    printf("\nreplacing p with %sp in quantified formula! debug me\n\n", STR_NOT_MINUS);
    exit( 1 );
  case AND:
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      replace_not_p_with_n_in_wff( p, n, &i );
    }
    break;
  case NOT: 
    if ( (*w)->son->fact->predicate == p ) {
      (*w)->connective = ATOM;
      (*w)->NOT_p = p;
      (*w)->fact = (*w)->son->fact;
      (*w)->fact->predicate = n;
      free( (*w)->son );
      (*w)->son = NULL;
    }
    break;
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: replace p with %sp, non logical %d\n\n",
	   STR_NOT_MINUS,
	   (*w)->connective);
    exit( 1 );
  }

}



void add_to_initial_state( int p, int n, int index )

{

  int i, j;
  Facts *tmp;
  
  if ( index == garity[p] ) {
    /* see if contrary fact is there in ini
     */
    for ( i = 0; i < gnum_initial_predicate[p]; i++ ) {
      for ( j = 0; j < garity[p]; j++ ) {
	if ( ginitial_predicate[p][i].args[j] != lconsts[j] ) {
	  break;
	}
      }
      if ( j == garity[p] ) {
	break;      }
    }
    if ( i < gnum_initial_predicate[p] ) {
      return;
    }

    /* no: add new fact to ini
     */
    ginitial_predicate[n][gnum_initial_predicate[n]].predicate = n;
    for ( i = 0; i < garity[n]; i++ ) {
      ginitial_predicate[n][gnum_initial_predicate[n]].args[i] = lconsts[i];
    }
    gnum_initial_predicate[n]++;

    if ( !gis_added[n] &&
	 !gis_deleted[n] ) {
      return;
    }

    /*
     * DEA - University of Brescia
     */


    /**
     * Aggiungo un fatto allo stato iniziale solo se non � derivato
     **
     * Add a new fact to the initial state only if it is not a derived fact 
     **/
    if (gpredicates_type[p] != IS_DERIVED)
      {

	/*
	 * End of DEA
	 */ 

        tmp = new_Facts();
        tmp->fact->predicate = n;
      	for ( i = 0; i < garity[p]; i++ ) {
          tmp->fact->args[i] = lconsts[i];
      	}
        tmp->next = ginitial;
        ginitial = tmp;
        gnum_initial++;
      }
    
    return;
  }
  
  for ( i = 0; i < gtype_size[gpredicates_args_type[p][index]]; i++ ) {
    lconsts[index] = gtype_consts[gpredicates_args_type[p][index]][i];
    add_to_initial_state( p, n, index + 1 );
  }

}











/*******************************************************************
 * SPLIT DOMAIN IN PREPARATION FOR SEPARATE INSTANTIATION ROUTINES *
 *******************************************************************/



int count_all_facts(WffNode *w) {
  
  WffNode *tmp;
  int counter = 0;

  if (w == NULL)
    return counter;

  switch (w->connective) {
  case OR:
  case AND:
    for (tmp = w->sons; tmp; tmp = tmp->next)
      counter += count_all_facts(tmp);
    break;
  case NOT:
    counter += count_all_facts(w->son);
    break;
  case ATOM:
    if (w->fact->predicate >= 0)
      counter++;
    break;
  default:
    break;
  }

  return counter;

}



void add_or_preconditions(WffNode *w, NormOperator *op, Bool first) {

  int m, j;
  WffNode *ww;
  Fact *tmp_ft;

  if (w == NULL)
    return;

  if (first) {
    op->num_or_precs = 0;
    m = count_all_facts(w);

    if (m == 0)
      return;
    
    op->or_precs = ( Fact * ) calloc( m, sizeof( Fact ) );
  }

  switch (w->connective) {
  case BIN_COMP:
    break;
  case OR:
  case AND:
    for (ww = w->sons; ww; ww = ww->next)
      add_or_preconditions(ww, op, FALSE);
    break;
  case NOT:
    add_or_preconditions(w->son, op, FALSE);
    break;
  case ATOM:
    if (w->fact->predicate < 0)
      break;
    tmp_ft = &op->or_precs[op->num_or_precs];
    op->num_or_precs++;
    tmp_ft->predicate = w->fact->predicate;
    for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
      tmp_ft->args[j] = w->fact->args[j];
    }
    break;
  default:
#ifdef __MY_OUTPUT__
    printf("Warning: unexpected node in add_or_preconditions()");
#endif
    break;
  }

}



void make_norm_operator(Operator_pointer p, NormOperator_pointer *out, int *count) {
  int j, a, m;
  WffNode *w, *ww, *www;
  NormOperator *tmp_op;
  Fact *tmp_ft;
  PlNode *pl;
  VarList *inst_var;
 
  w = p -> preconds;
  switch ( w->connective ) {
  case OR:
    for ( ww = w->sons; ww; ww = ww->next ) {
      tmp_op = new_NormOperator( p );
      add_or_preconditions(w, tmp_op, TRUE);
      if ( ww->connective == AND ) {
	m = 0; 
	for ( www = ww->sons; www; www = www->next ) 
	  if (www->connective != BIN_COMP) m++;
	tmp_op->preconds = ( Fact * ) calloc( m, sizeof( Fact ) );
	for ( www = ww->sons; www; www = www->next ) {
	  tmp_ft = &(tmp_op->preconds[tmp_op->num_preconds]);
	  /* no ATOM --> NOT with EQ son after our preprocessing.
	   * encode not eq with -2
	   */

	  /*
	   * DEA - University of Brescia
	   */

	  /**
	   * Le precondizioni numeriche vengono inserite nel norm_operator come PlNode.
	   * Saranno tradotte in seguito.
	   **
	   * Numeric preconditions are copied as PlNodes in the norm_operator.
	   * They will be translated after.
	   **/
	  if (www->connective == BIN_COMP)
	    {
	      if (!tmp_op->numeric)
		tmp_op->numeric = copy_PlNode(www->numeric);
	      else
		{
		  for (pl = tmp_op->numeric; pl && pl->next; pl = pl->next);
		  pl->next =  copy_PlNode(www->numeric);
		}

	      if (!tmp_op->instantiated_vars)
		tmp_op->instantiated_vars = copy_VarList(www->instantiated_vars);
	      else
		{
		  for (inst_var = tmp_op->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
		  inst_var->next = copy_VarList(www->instantiated_vars);
		}

	      continue;
	    }

	  /**
	   * Marco questo fatto se rappresentava una precondizione implicita
	   * di disugualianza tra parametri
	   **
	   * Mark this fact if it represent an implicit precondition
	   * (a disequal condition among operator's parameters)
	   **/
	  tmp_ft->added_implicit = www->fact->added_implicit;
	  tmp_ft->is_start_end_ovr = www->is_start_end_ovr;

	  /*
	   * End of DEA
	   */

	  tmp_ft->predicate = ( www->connective == ATOM ) ? 
	    www->fact->predicate : -2;
	  a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	    2 : garity[tmp_ft->predicate];
	  for ( j = 0; j < a; j++ ) {
	    tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	      www->son->fact->args[j] : www->fact->args[j];
	  }
	  tmp_op->num_preconds++;
	}
      } else {
	
	/*
	 * DEA - University of Brescia
	 */
	
	/**
	 * Le precondizioni numeriche vengono inserite nel norm_operator come PlNode.
	 * Saranno tradotte in seguito.
	 **
	 * Numeric preconditions are copied as PlNodes in the norm_operator.
	 * They will be translated after.
	 **/
	if (ww->connective == BIN_COMP)
	  {
	    if (!tmp_op->numeric)
	      tmp_op->numeric = copy_PlNode(ww->numeric);
	    else
	      {
		for (pl = tmp_op->numeric; pl && pl->next; pl = pl->next);
		pl->next =  copy_PlNode(ww->numeric);
	      }

	    if (!tmp_op->instantiated_vars)
	      tmp_op->instantiated_vars = copy_VarList(ww->instantiated_vars);
	    else
	      {
		for (inst_var = tmp_op->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
		inst_var->next = copy_VarList(ww->instantiated_vars);
	      }
	  }

	/*
	 * End of DEA
	 */

	else
	  {
	    tmp_op->preconds = ( Fact * ) calloc( 1, sizeof( Fact ) );
	    tmp_ft = &(tmp_op->preconds[0]);
	    
	    /*
	     * DEA - University of Brescia
	     */
	    
	    tmp_ft->added_implicit = ww->fact->added_implicit;
	    tmp_ft->is_start_end_ovr = ww->is_start_end_ovr;

	    /*
	     * End of DEA
	     */

	    tmp_ft->predicate = ( ww->connective == ATOM ) ? 
	      ww->fact->predicate : -2;
	    a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	      2 : garity[tmp_ft->predicate];
	    for ( j = 0; j < a; j++ ) {
	      tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
		ww->son->fact->args[j] : ww->fact->args[j];
	    }
	    tmp_op->num_preconds = 1;
	  }
      }
      make_normal_effects( &tmp_op, p );
      out[(*count)++] = tmp_op;
    }
    break;
  case AND:
    tmp_op = new_NormOperator( p );
    m = 0; 
    for ( ww = w->sons; ww; ww = ww->next )
      if (ww->connective != BIN_COMP) m++;
    tmp_op->preconds = ( Fact * ) calloc( m, sizeof( Fact ) );
    for ( ww = w->sons; ww; ww = ww->next ) {
      tmp_ft = &(tmp_op->preconds[tmp_op->num_preconds]);
	
      /*
       * DEA - University of Brescia
       */
      
      /**
       * Le precondizioni numeriche vengono inserite nel norm_operator come PlNode.
       * Saranno tradotte in seguito.
       **
       * Numeric preconditions are copied as PlNodes in the norm_operator.
       * They will be translated after.
       **/
      if (ww->connective == BIN_COMP)
	{
	  if (!tmp_op->numeric)
	    tmp_op->numeric = copy_PlNode(ww->numeric);
	  else
	    {
	      for (pl = tmp_op->numeric; pl && pl->next; pl = pl->next);
	      pl->next =  copy_PlNode(ww->numeric);
	    }

	  if (!tmp_op->instantiated_vars)
	    tmp_op->instantiated_vars = copy_VarList(ww->instantiated_vars);
	  else
	    {
	      for (inst_var = tmp_op->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
	      inst_var->next = copy_VarList(ww->instantiated_vars);
	    }

	  continue;
	}

      /*
       * End of DEA
       */

      if (ww->connective == ATOM) 
	{
	  tmp_ft->added_implicit = ww->fact->added_implicit;
	  tmp_ft->is_start_end_ovr = ww->is_start_end_ovr;
	}
      else
	{
	  tmp_ft->added_implicit = ww->son->fact->added_implicit;
	  tmp_ft->is_start_end_ovr = ww->son->is_start_end_ovr;
	}
      
      tmp_ft->predicate = ( ww->connective == ATOM ) ? 
	ww->fact->predicate : -2;
      a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	2 : garity[tmp_ft->predicate];
      for ( j = 0; j < a; j++ ) {
	tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	  ww->son->fact->args[j] : ww->fact->args[j];
      }
      tmp_op->num_preconds++;
    }
    make_normal_effects( &tmp_op, p );
    out[(*count)++] = tmp_op;
    break;
  case NOT:
  case ATOM:
    tmp_op = new_NormOperator( p );
    tmp_op->preconds = ( Fact * ) calloc( 1, sizeof( Fact ) );
    tmp_ft = &(tmp_op->preconds[0]);
    tmp_ft->added_implicit = w->fact->added_implicit;
    tmp_ft->is_start_end_ovr = w->is_start_end_ovr;
    tmp_ft->predicate = ( w->connective == ATOM ) ? 
      w->fact->predicate : -2;
    a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
      2 : garity[tmp_ft->predicate];
    for ( j = 0; j < a; j++ ) {
      tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	w->son->fact->args[j] : w->fact->args[j];
    }
    tmp_op->num_preconds = 1;
    make_normal_effects( &tmp_op, p );
    out[(*count)++] = tmp_op;
    break;
	
    /*
     * DEA - University of Brescia
     */
    
    /**
     * Le precondizioni numeriche vengono inserite nel norm_operator come PlNode.
     * Saranno tradotte in seguito.
     * Vengono gestiti operatori con sole precondizioni numeriche
     **
     * Numeric preconditions are copied as PlNodes in the norm_operator.
     * They will be translated after.
     **/
  case BIN_COMP:
    tmp_op = new_NormOperator( p );
    if (!tmp_op->numeric)
      tmp_op->numeric = copy_PlNode(w->numeric);
    else
      {
	for (pl = tmp_op->numeric; pl && pl->next; pl = pl->next);
	pl->next =  copy_PlNode(w->numeric);
      }
    if (!tmp_op->instantiated_vars)
      tmp_op->instantiated_vars = copy_VarList(w->instantiated_vars);
    else
      {
	for (inst_var = tmp_op->instantiated_vars; inst_var && inst_var->next; inst_var = inst_var->next);
	inst_var->next = copy_VarList(w->instantiated_vars);
      }
    make_normal_effects( &tmp_op, p );
    out[(*count)++] = tmp_op;
    break;

    /*
     * End of DEA
     */

  case TRU:
    tmp_op = new_NormOperator( p );
    make_normal_effects( &tmp_op, p );
    out[(*count)++] = tmp_op;
    break;
  case FAL:
    break;
  default:
    printf("\nwon't get here: non OR, AND, ATOM, TRUE, FALSE in dnf. debug me\n\n");
    exit( 1 );
  }
  
}






void split_domain( void )

{

  int i, m, s = 0;
  Effect *e;

  for ( i = 0; i < MAX_TYPES; i++ ) {
    gnum_intersected_types[i] = -1;
  }

  for ( i = 0; i < gnum_operators; i++ ) {
    if ( (m = is_dnf( goperators[i]->preconds )) != -1 ) {
      for ( e = goperators[i]->effects; e; e = e->next ) {
	if ( is_dnf( e->conditions ) == -1 ) {
	  break;
	}
      }
      if ( !e ) {
	goperators[i]->hard = FALSE;
	s += m;
      }
    }
  }

  ghard_operators = ( Operator_pointer * ) calloc( MAX_OPERATORS, sizeof( Operator ) );
  gnum_hard_operators = 0; 
  geasy_operators = ( NormOperator_pointer * ) calloc( s, sizeof( NormOperator_pointer ) );
  gnum_easy_operators = 0;

 /*
  * DEA - University of Brescia
  */

  /**
   * Divido i predicati derivati in easy e hard
   **
   * Split derived predicates into easy and hard
   **/
  if (GpG.derived_predicates) {
    s = m = 0;
    for ( i = 0; i < gnum_derived_predicates; i++ ) {
      if ( (m = is_dnf( gderivedpred[i]->preconds )) != -1 ) {
	for ( e = gderivedpred[i]->effects; e; e = e->next ) {
	  if ( is_dnf( e->conditions ) == -1 ) {
	    break;
	  }
	}
	if ( !e ) {
	  gderivedpred[i]->hard = FALSE;
	  s += m;
	}
      }
    }

    ghard_derivedpred = ( Operator_pointer * ) calloc( MAX_DERIVED_PREDICATES, sizeof( Operator ) );
    gnum_hard_derivedpred = 0; 
    geasy_derivedpred = ( NormOperator_pointer * ) calloc( s, sizeof( NormOperator_pointer ) );
    gnum_easy_derivedpred = 0;
  }
  /*
   * End of DEA
   */

  for ( i = 0; i < gnum_operators; i++ ) {
    if ( goperators[i]->hard ) {
      ghard_operators[gnum_hard_operators++] = goperators[i];
      continue;
    }
    make_norm_operator(goperators[i], geasy_operators, &gnum_easy_operators);
  }

  /*
   * DEA - University of Brescia
   */
  
  /**
   * Costruisco la lista dei predicati derivati hard
   **
   * Build the list of hard derived predicates
   **/
  if (GpG.derived_predicates) {
    for ( i = 0; i < gnum_derived_predicates; i++ ) {
      if ( gderivedpred[i]->hard ) {
	ghard_derivedpred[gnum_hard_derivedpred++] = gderivedpred[i];
	continue;
      }
      make_norm_operator(gderivedpred[i], geasy_derivedpred, &gnum_easy_derivedpred);
    }
  }

  /*
   * End of DEA
   */

  if (gcmd_line.display_info == 109 ) {
    printf("\n\nsplitted operators are:\n");

    printf("\nEASY:\n");
    for ( i = 0; i < gnum_easy_operators; i++ ) {
      print_NormOperator( geasy_operators[i] );
    }

    printf("\n\n\nHARD:\n");
    for ( i = 0; i < gnum_hard_operators; i++ ) {
      print_Operator( ghard_operators[i] );
    }
  }


  if (gcmd_line.display_info == 109 ) {
    printf("\n\nDP splitted operators are:\n");
    
    printf("\nEASY:\n");
    for ( i = 0; i < gnum_easy_derivedpred; i++ ) {
      print_NormOperator( geasy_derivedpred[i] );
    }

    printf("\n\n\nHARD:\n");
    for ( i = 0; i < gnum_hard_derivedpred; i++ ) {
      print_Operator( ghard_derivedpred[i] );
    }
  }

}



int is_dnf( WffNode *w )

{

  WffNode *i;
  int s = 0;

  switch ( w->connective ) {
  case ALL:
  case EX:
    printf("\nchecking quantifier for dnf. debug me\n\n");
    exit( 1 );
  case AND:
    for ( i = w->sons; i; i = i->next ) {
      if ( i->connective == ATOM ||
	   i->connective == BIN_COMP ||
	   ( i->connective == NOT
	     && i->son->fact->predicate == -1 ) ) {
	continue;
      }
      return -1;
    }
    return 1;
  case OR:
    for ( i = w->sons; i; i = i->next ) {
      s++;
      if ( i->connective == ATOM ||
	   i->connective == BIN_COMP ||
	   ( i->connective == NOT &&
	     i->son->fact->predicate == -1 ) ||
	   ( i->connective == AND &&
	     is_dnf( i ) != -1 ) ) {
	continue;
      }
      return -1;
    }
    return s;
  case NOT:
    if ( w->son->fact->predicate == -1 ) {
      return 1;
    } else {
      printf("\nNOT with non eq - son in presimplified formula. debug me\n\n");
      exit( 1 );
    }
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    return 1;
  default:
    printf("\nwon't get here: check dnf, non logical %d\n\n",
	   w->connective);
    exit( 1 );
  }

}



void make_normal_effects( NormOperator **nop, Operator *op )

{

  Effect *e;
  NormEffect *tmp_ef;
  WffNode *w, *ww, *www;
  int j, a, m, ma, md;
  Literal *l;
  Fact *tmp_ft;

  for ( e = op->effects; e; e = e->next ) {
    w = e->conditions;
    switch ( w->connective ) {
    case OR:
      for ( ww = w->sons; ww; ww = ww->next ) {
	tmp_ef = new_NormEffect1( e );
	if ( ww->connective == AND ) {
	  m = 0;
	  for ( www = ww->sons; www; www = www->next ) m++;
	  tmp_ef->conditions = ( Fact * ) calloc( m, sizeof( Fact ) );
	  for ( www = ww->sons; www; www = www->next ) {
	    tmp_ft = &(tmp_ef->conditions[tmp_ef->num_conditions]);
	    tmp_ft->is_start_end_ovr = www->is_start_end_ovr;
	    tmp_ft->predicate = ( www->connective == ATOM ) ?
	      www->fact->predicate : -2;
	    a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	      2 : garity[tmp_ft->predicate];
	    for ( j = 0; j < a; j++ ) {
	      tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
		www->son->fact->args[j] : www->fact->args[j];
	    }
	    tmp_ef->num_conditions++;
	  }
	} else {
	  tmp_ef->conditions = ( Fact * ) calloc( 1, sizeof( Fact ) );
	  tmp_ft = &(tmp_ef->conditions[0]);
	  tmp_ft->is_start_end_ovr = ww->is_start_end_ovr;
	  tmp_ft->predicate = ( ww->connective == ATOM ) ? 
	    ww->fact->predicate : -2;
	  a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	    2 : garity[tmp_ft->predicate];
	  for ( j = 0; j < a; j++ ) {
	    tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	      ww->son->fact->args[j] : ww->fact->args[j];
	  }
	  tmp_ef->num_conditions = 1;
	}
	ma = 0;
	md = 0;
	for ( l = e->effects; l; l = l->next ) {
	  if ( l->negated ) {
	    md++;
	  } else {
	    ma++;
	  }
	}
	tmp_ef->adds = ( Fact * ) calloc( ma, sizeof( Fact ) );
	tmp_ef->dels = ( Fact * ) calloc( md, sizeof( Fact ) );
	for ( l = e->effects; l; l = l->next ) {
	  if ( l->negated ) {
	    tmp_ft = &(tmp_ef->dels[tmp_ef->num_dels++]);
	  } else {
	    tmp_ft = &(tmp_ef->adds[tmp_ef->num_adds++]);
	  }
	  tmp_ft->is_start_end_ovr = l->fact.is_start_end_ovr;
	  tmp_ft->predicate = l->fact.predicate;
	  for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
	    tmp_ft->args[j] = l->fact.args[j];
	  }
	}
	tmp_ef->next = (*nop)->effects;
	if ( (*nop)->effects ) {
	  (*nop)->effects->prev = tmp_ef;
	}
	(*nop)->effects = tmp_ef;
      }
      break;
    case AND:
      tmp_ef = new_NormEffect1( e );
      m = 0;
      for ( ww = w->sons; ww; ww = ww->next ) m++;
      tmp_ef->conditions = ( Fact * ) calloc( m, sizeof( Fact ) );
      for ( ww = w->sons; ww; ww = ww->next ) {
	tmp_ft = &(tmp_ef->conditions[tmp_ef->num_conditions]);
	tmp_ft->is_start_end_ovr = ww->is_start_end_ovr;
	tmp_ft->predicate = ( ww->connective == ATOM ) ? 
	  ww->fact->predicate : -2;
	a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	  2 : garity[tmp_ft->predicate];
	for ( j = 0; j < a; j++ ) {
	  tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	    ww->son->fact->args[j] : ww->fact->args[j];
	}
	tmp_ef->num_conditions++;
      }
      ma = 0;
      md = 0;
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  md++;
	} else {
	  ma++;
	}
      }
      tmp_ef->adds = ( Fact * ) calloc( ma, sizeof( Fact ) );
      tmp_ef->dels = ( Fact * ) calloc( md, sizeof( Fact ) );
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  tmp_ft = &(tmp_ef->dels[tmp_ef->num_dels++]);
	} else {
	  tmp_ft = &(tmp_ef->adds[tmp_ef->num_adds++]);
	}
	tmp_ft->is_start_end_ovr = l->fact.is_start_end_ovr;
	tmp_ft->predicate = l->fact.predicate;
	for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
	  tmp_ft->args[j] = l->fact.args[j];
	}
      }
      tmp_ef->next = (*nop)->effects;
      if ( (*nop)->effects ) {
	(*nop)->effects->prev = tmp_ef;
      }
      (*nop)->effects = tmp_ef;
      break;
    case NOT:
    case ATOM:
      tmp_ef = new_NormEffect1( e );
      tmp_ef->conditions = ( Fact * ) calloc( 1, sizeof( Fact ) );
      tmp_ft = &(tmp_ef->conditions[0]);
      tmp_ft->is_start_end_ovr = w->is_start_end_ovr;
      tmp_ft->predicate = ( w->connective == ATOM ) ? 
	w->fact->predicate : -2;
      a = ( tmp_ft->predicate == -1 || tmp_ft->predicate == -2 ) ?
	2 : garity[tmp_ft->predicate];
      for ( j = 0; j < a; j++ ) {
	tmp_ft->args[j] = ( tmp_ft->predicate == -2 ) ? 
	  w->son->fact->args[j] : w->fact->args[j];
      }
      tmp_ef->num_conditions = 1;
      ma = 0;
      md = 0;
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  md++;
	} else {
	  ma++;
	}
      }
      tmp_ef->adds = ( Fact * ) calloc( ma, sizeof( Fact ) );
      tmp_ef->dels = ( Fact * ) calloc( md, sizeof( Fact ) );
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  tmp_ft = &(tmp_ef->dels[tmp_ef->num_dels++]);
	} else {
	  tmp_ft = &(tmp_ef->adds[tmp_ef->num_adds++]);
	}
	tmp_ft->is_start_end_ovr = l->fact.is_start_end_ovr;
	tmp_ft->predicate = l->fact.predicate;
	for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
	  tmp_ft->args[j] = l->fact.args[j];
	}
      }
      tmp_ef->next = (*nop)->effects;
      if ( (*nop)->effects ) {
	(*nop)->effects->prev = tmp_ef;
      }
      (*nop)->effects = tmp_ef;
      break;     
    case TRU:
      tmp_ef = new_NormEffect1( e );
      ma = 0;
      md = 0;
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  md++;
	} else {
	  ma++;
	}
      }
      tmp_ef->adds = ( Fact * ) calloc( ma, sizeof( Fact ) );
      tmp_ef->dels = ( Fact * ) calloc( md, sizeof( Fact ) );
      for ( l = e->effects; l; l = l->next ) {
	if ( l->negated ) {
	  tmp_ft = &(tmp_ef->dels[tmp_ef->num_dels++]);
	} else {
	  tmp_ft = &(tmp_ef->adds[tmp_ef->num_adds++]);
	}
	tmp_ft->is_start_end_ovr = l->fact.is_start_end_ovr;
	tmp_ft->predicate = l->fact.predicate;
	for ( j = 0; j < garity[tmp_ft->predicate]; j++ ) {
	  tmp_ft->args[j] = l->fact.args[j];
	}
      }
      tmp_ef->next = (*nop)->effects;
      if ( (*nop)->effects ) {
	(*nop)->effects->prev = tmp_ef;
      }
      (*nop)->effects = tmp_ef;
      break;
    case FAL:
      break;
    default:
      printf("\nwon't get here: non OR, AND, ATOM, TRUE, FALSE in dnf. debug me\n\n");
      exit( 1 );
    }
  }

}









/*************************************************************************
 * ADDITIONAL: FULL DNF, only compute on fully instantiated formulae!!!! *
 *************************************************************************/










/* dnf
 */

WffNode *lhitting_sets;
WffNode_pointer *lset;
int lmax_set;






void dnf( WffNode **w )

{

  static Bool first_call = TRUE;

  if ( first_call ) {
    lset = ( WffNode_pointer * ) 
      calloc( MAX_HITTING_SET_DEFAULT, sizeof( WffNode_pointer ) );
    lmax_set = MAX_HITTING_SET_DEFAULT;
    first_call = FALSE;
  }

  ANDs_below_ORs_in_wff( w );

}



void ANDs_below_ORs_in_wff( WffNode **w )

{

  WffNode *i, *tmp;
  int c, m;

  switch ( (*w)->connective ) {
  case ALL:
  case EX:
    printf("\ntrying to put quantified formula into DNF! (ands down) debug me\n\n");
    exit( 1 );
    break;
  case AND:
    c = 0;
    m = 0;
    for ( i = (*w)->sons; i; i = i->next ) {
      ANDs_below_ORs_in_wff( &i );
      if ( i->connective == OR ) {
	c++;
      }
      m++;
    }
    if ( c == 0 ) {
      /* no ORs as sons --> all sons are literals. OK
       */
      merge_next_step_ANDs_and_ORs_in_wff( w );
      break;
    }
    /* crucial part: AND node, sons can be merged OR's.
     * (i.e., sons are either literals or disjunctions of 
     * conjunctions of literals)
     * create OR node with one hitting set of w's sons for 
     * each disjunct
     */
    lhitting_sets = NULL;
    if ( m > lmax_set ) {
      free( lset );
      lset = ( WffNode_pointer * ) calloc( m, sizeof( WffNode_pointer ) );
      lmax_set = m;
    }
    collect_hitting_sets( (*w)->sons, 0 );
    (*w)->connective = OR;
    tmp = (*w)->sons;
    (*w)->sons = lhitting_sets;
    free_WffNode( tmp );
    merge_next_step_ANDs_and_ORs_in_wff( w );
    break;
  case OR:
    for ( i = (*w)->sons; i; i = i->next ) {
      ANDs_below_ORs_in_wff( &i );
    }
    merge_next_step_ANDs_and_ORs_in_wff( w );
    break;
  case NOT:
  case ATOM:
  case TRU:
  case FAL:
  case BIN_COMP:
    break;
  default:
    printf("\nwon't get here: ands down, non logical %d\n\n",
	   (*w)->connective);
    exit( 1 );
  }

}



void collect_hitting_sets( WffNode *ORlist, int index )

{

  WffNode *tmp1, *tmp2, *j;
  int i;

  if ( !ORlist ) {
    tmp1 = new_WffNode( AND );
    for ( i = 0; i < index; i++ ) {
      tmp2 = copy_Wff( lset[i] );
      tmp2->next = tmp1->sons;
      if ( tmp1->sons ) {
	tmp1->sons->prev = tmp2;
      }
      tmp1->sons = tmp2;
    }
    tmp1->next = lhitting_sets;
    if ( lhitting_sets ) {
      lhitting_sets->prev = tmp1;
    }
    lhitting_sets = tmp1;
    return;
  }

  if ( ORlist->connective != OR ) {
    lset[index] = ORlist;
    collect_hitting_sets( ORlist->next, index + 1 );
    return;
  }

  for ( j = ORlist->sons; j; j = j->next ) {
    lset[index] = j;
    collect_hitting_sets( ORlist->next, index + 1 );
  }

}



void merge_next_step_ANDs_and_ORs_in_wff( WffNode **w )

{

  WffNode *i, *j, *tmp;

  i = (*w)->sons;
  while ( i ) {
    if ( i->connective == (*w)->connective ) {
      if ( !(i->sons) ) {
	if ( i->next ) {
	  i->next->prev = i->prev;
	}
	if ( i->prev ) {
	  i->prev->next = i->next;
	} else {
	  (*w)->sons = i->next;
	}
	tmp = i;
	i = i->next;
	free( tmp );
	continue;
      }
      for ( j = i->sons; j->next; j = j->next );
      j->next = i->next;
      if ( i->next ) {
	i->next->prev = j;
      }
      if ( i->prev ) {
	i->prev->next = i->sons;
	i->sons->prev = i->prev;
      } else {
	(*w)->sons = i->sons;
      }
      tmp = i;
      i = i->next;
      free( tmp );
      continue;
    }
    i = i->next;
  }

}


/*   switch ( (*w)->connective ) { */
/*   case ALL: */
/*   case EX: */
/*     break; */
/*   case AND: */
/*   case OR: */
/*     for ( i = (*w)->sons; i; i = i->next ) { */
/*     } */
/*     break; */
/*   case NOT: */
/*     break; */
/*   case ATOM: */
/*   case TRU: */
/*   case FAL: */
/*     break; */
/*   default: */
/*     printf("\nwon't get here: remove var, non logical %d\n\n", */
/* 	   (*w)->connective); */
/*     exit( 1 ); */
/*   } */



Bool check_for_recursive_rules(void)
{
  int i, j, ef_pred, num_ax_block;
  int **uses;

  num_ax_block = (gnum_derived_predicates >> 5) + 1;
  
  //Un bit settato nella posizione <j,i> di uses indica che 
  //l'assioma j usa l'effetto dell'assioma i 
  uses = alloc_matrix(gnum_derived_predicates, num_ax_block);

  for (i = 0; i < gnum_derived_predicates; i++)
    {
      ef_pred = gderivedpred[i]->effects->effects->fact.predicate;

      for (j = 0; j < gnum_derived_predicates; j++)
	if (GET_BIT(rules_precs[j], ef_pred))
	  {
	    if (i == j)
	      {
		free_matrix(uses);
		free_matrix(rules_precs);

		//Se un assioma usa se stesso allora c'� ricorsione, 
		//non occorre continuare.
		return TRUE;
	      }

	    SET_BIT(uses[j], i);
	  }
    }

  for (i = 0; i < gnum_derived_predicates; i++)
    {
      int visited[num_ax_block];
      register int temp, y, m, n, k;
      
      j = 0;
      memset(visited, 0, num_ax_block * sizeof(int));

      m = 0;

      while (m < num_ax_block)
	{
	  temp = uses[i][m];
	  
	  y = 32;

	  while (temp)
	    {
	      y--;

	      if (temp & FIRST_1)
		{
		  n = (m << 5) + y;

		  if (n == i)
		    {
		      free_matrix(uses);
		      free_matrix(rules_precs);
		      return TRUE;
		    }

		  if (GET_BIT(visited, n))
		    {
		      temp <<= 1;
		      continue;
		    }
		  
		  SET_BIT(visited, n);
		  
		  for (k = 0; k < num_ax_block; k++)
		    uses[i][k] |= uses[n][k];

		  if (GET_BIT(uses[i], i))
		    {
		      free_matrix(uses);
		      free_matrix(rules_precs);
		      return TRUE;
		    }

		  m = -1;
		  break; //break while => vado a (**) e ricomincio dal blocco 0
		}

	      temp <<= 1;
	    }
	  
	  m++; //(**)
	}
	      
      /*

      while (j < gnum_derived_predicates)
	{
	  if (GET_BIT(visited, j))
	    {
	      j++;
	      continue;
	    }

	  SET_BIT(visited, j);
	  
	  if (GET_BIT(uses[i], j))
	    {
	      for (k = 0; k < num_ax_block; k++)
		uses[i][k] |= uses[j][k];
	      
	      if (GET_BIT(uses[i], i))
		{
		  free(uses[0]);
		  free(uses);
		  
		  return TRUE;
		}
	      
	      j = 0;
	    }
	  else
	    j++;
	}


      */

    }

  free_matrix(uses);
  free_matrix(rules_precs);

  return FALSE;
}
