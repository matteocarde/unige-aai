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
 * File: inst_pre.h
 * Description: headers for instantiating operators, preprocessing part.
 *              - transform domain into integers
 *              - inertia preprocessing:
 *                  - collect inertia info
 *                  - split initial state in special arrays
 *              - Wff normalization:
 *                  - simplification
 *                  - quantifier expansion
 *                  - NOT s down
 *              - negative preconditions translation
 *              - split operators into easy and hard to instantiate ones
 *
 *              - full DNF functions, only feasible for fully instantiated 
 *                formulae
 *
 * Author: Joerg Hoffmann 2000
 *
 *********************************************************************/ 











#ifndef _INST_PRE_H
#define _INST_PRE_H



void encode_domain_in_integers( void );
void collect_all_strings( void );
int position_in_types_table( char *str );
int position_in_constants_table( char *str );
int position_in_predicates_table( char *str );
void create_integer_representation( void );
void make_Fact( Fact *f, PlNode *n, int num_vars );
/* Timed initial Facts PDDL2.2 */
void add_Timed_Facts_to_ops( PlOperator **ops );
void clear_Timed_Fact_Nodes( void );
/* PDDL2.2*/
Bool is_subtype( int t1, int t2 );
WffNode *make_Wff( PlNode *p, int num_vars );
Effect *make_effect( PlNode *p, int num_vars );



void do_inertia_preprocessing_step_1( void );
void collect_inertia_information( void );
void split_initial_state( void );



void normalize_all_wffs( void );
void remove_unused_vars_in_wff( WffNode **w );
void decrement_inferior_vars( int var, WffNode *w );
Bool var_used_in_wff( int code_var, WffNode *w );
void simplify_wff( WffNode **w );
void expand_quantifiers_in_wff( WffNode **w, char *var_name, int var, int constant );
WffNode *copy_Wff( WffNode *w );
Bool possibly_positive( Fact *f );
Bool possibly_negative( Fact *f );
Bool matches( Fact *f1, Fact *f2 );
void cleanup_wff( WffNode **w );
void detect_tautologies_in_wff( WffNode **w );
Bool are_identical_ATOMs( WffNode *w1, WffNode *w2 );
void merge_ANDs_and_ORs_in_wff( WffNode **w );
void NOTs_down_in_wff( WffNode **w );



void translate_negative_preconds( void );
Bool translate_one_negative_cond( WffNode *w );
void replace_not_p_with_n_in_wff( int p, int n, WffNode **w );
void add_to_initial_state( int p, int n, int index );



void split_domain( void );
int is_dnf( WffNode *w );
void  make_normal_effects( NormOperator **nop, Operator *op );



void dnf( WffNode **w );
void ANDs_below_ORs_in_wff( WffNode **w );
void collect_hitting_sets( WffNode *ORlist, int index );
void merge_next_step_ANDs_and_ORs_in_wff( WffNode **w );

Bool check_for_recursive_rules(void);
void reverse_numeric_condition(PlNode *p);

int count_all_facts(WffNode *w);

#endif /* _INST_PRE_H */
