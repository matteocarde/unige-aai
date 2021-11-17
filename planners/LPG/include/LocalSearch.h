 /*********************************************************************
 * (C) Copyright 2002  Universita' degli Studi di Brescia
 *     Dipartimento di Elettronica per l'Automazione
 *     Via Branze 38, 25123 Brescia, Italy
 *
 * All rights reserved. Use of this software is permitted ONLY for
 * non-commercial research purposes, and it may be copied only
 * for that use only. All copies must include this copyright message.
 * This software is made available AS IS, and neither the authors
 * nor the University of Brescia make any warranty about the
 * software or its performance.
 *
 *********************************************************************/





 
/********************************************************************
 * File: LocalSearch.h
 * Description: header file for local-search strategies
 *
 *   PDDL 2.1 version without conditional and quantified effects 
 *
 * Authors: Alfonso Gerevini, Marco Lazzaroni, Alessandro Saetti, 
 *          Ivan Serina, Sergio Spinoni
 *
 *********************************************************************/ 

 


#ifndef __LOCSEARCH_H 
#define __LOCSEARCH_H  

int LocalSearch (State * start_state, State * end_state, PlanAction ** plan_actions);

int not_tabu (int tofix);

int action_eff_cost (register ActNode_list infAction);

float find_min (constraints_list inf_tofix, int *pos_temp_vect, int num, int *num_min, int *num_neg);

float check_value (float new_value);

int define_neighborhood (register FctNode_list node_tofix, int initialize);

int define_restricted_neighborhood (register FctNode_list node_tofix, int initialize);

int define_neighborhood_for_threats (register NoopNode_list node_tofix,int initialize);

void update_mutex_multilevel (int level,int pos_action);

void update_mutex (int pos_action);

void insert_els_in_neighborhood (IntList * ilist, action_set * neighbors);

float action_cost (neighb_list Action);

void create_remotion_neighborhood_for_compvar (int fct_pos, int level);

int define_neighborhood_for_compvar_in_down_level (int numeric_fact, action_set *neighbors, int level);

#endif
