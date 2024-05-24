/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_lr_table_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:54 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_LR_TABLE_BONUS_H
# define INSERT_LR_TABLE_BONUS_H

/* ****************************** ACTION TABLE ****************************** */
# define ACT_0   "|   |   |   |s8 |   |s10|s13|s14|s15|s16|   |"
# define ACT_1   "|s17|s18|   |   |   |   |   |   |   |   |acc|"
# define ACT_2   "|r1 |r1 |s19|   |r1 |   |   |   |   |   |r1 |"
# define ACT_3   "|r4 |r4 |r4 |   |r4 |   |   |   |   |   |r4 |"
# define ACT_4   "|r6 |r6 |r6 |   |r6 |   |   |   |   |   |r6 |"
# define ACT_5   "|r7 |r7 |r7 |   |r7 |   |s13|s14|s15|s16|r7 |"
# define ACT_6   "|r12|r12|r12|   |r12|s10|s13|s14|s15|s16|r12|"
# define ACT_7   "|r14|r14|r14|   |r14|s25|s13|s14|s15|s16|r14|"
# define ACT_8   "|   |   |   |s8 |   |s10|s13|s14|s15|s16|   |"
# define ACT_9   "|r20|r20|r20|   |r20|r20|r20|r20|r20|r20|r20|"
# define ACT_10  "|r15|r15|r15|   |r15|r15|r15|r15|r15|r15|r15|"
# define ACT_11  "|r22|r22|r22|   |r22|r22|r22|r22|r22|r22|r22|"
# define ACT_12  "|r23|r23|r23|   |r23|r23|r23|r23|r23|r23|r23|"
# define ACT_13  "|   |   |   |   |   |s28|   |   |   |   |   |"
# define ACT_14  "|   |   |   |   |   |s28|   |   |   |   |   |"
# define ACT_15  "|   |   |   |   |   |s28|   |   |   |   |   |"
# define ACT_16  "|   |   |   |   |   |s32|   |   |   |   |   |"
# define ACT_17  "|   |   |   |s8 |   |s10|s13|s14|s15|s16|   |"
# define ACT_18  "|   |   |   |s8 |   |s10|s13|s14|s15|s16|   |"
# define ACT_19  "|   |   |   |s8 |   |s10|s13|s14|s15|s16|   |"
# define ACT_20  "|r8 |r8 |r8 |   |r8 |   |s13|s14|s15|s16|r8 |"
# define ACT_21  "|r11|r11|r11|   |r11|s25|s13|s14|s15|s16|r11|"
# define ACT_22  "|r21|r21|r21|   |r21|r21|r21|r21|r21|r21|r21|"
# define ACT_23  "|r13|r13|r13|   |r13|s38|s13|s14|s15|s16|r13|"
# define ACT_24  "|r16|r16|r16|   |r16|r16|r16|r16|r16|r16|r16|"
# define ACT_25  "|r18|r18|r18|   |r18|r18|r18|r18|r18|r18|r18|"
# define ACT_26  "|s17|s18|   |   |s39|   |   |   |   |   |   |"
# define ACT_27  "|r24|r24|r24|   |r24|r24|r24|r24|r24|r24|r24|"
# define ACT_28  "|r27|r27|r27|   |r27|r27|r27|r27|r27|r27|r27|"
# define ACT_29  "|r25|r25|r25|   |r25|r25|r25|r25|r25|r25|r25|"
# define ACT_30  "|r26|r26|r26|   |r26|r26|r26|r26|r26|r26|r26|"
# define ACT_31  "|r28|r28|r28|   |r28|r28|r28|r28|r28|r28|r28|"
# define ACT_32  "|r29|r29|r29|   |r29|r29|r29|r29|r29|r29|r29|"
# define ACT_33  "|r2 |r2 |s19|   |r2 |   |   |   |   |   |r2 |"
# define ACT_34  "|r3 |r3 |s19|   |r3 |   |   |   |   |   |r3 |"
# define ACT_35  "|r5 |r5 |r5 |   |r5 |   |   |   |   |   |r5 |"
# define ACT_36  "|r10|r10|r10|   |r10|s38|s13|s14|s15|s16|r10|"
# define ACT_37  "|r17|r17|r17|   |r17|r17|r17|r17|r17|r17|r17|"
# define ACT_38  "|r19|r19|r19|   |r19|r19|r19|r19|r19|r19|r19|"
# define ACT_39  "|r9 |r9 |r9 |   |r9 |   |r9 |r9 |r9 |r9 |r9 |"

/* ******************************* GOTO TABLE ******************************* */
# define GOTO_0  "|  |1 |2 |3 |5 |4 |7 |  |6 |9 |11|  |12|  |"
# define GOTO_1  "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_2  "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_3  "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_4  "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_5  "|  |  |  |  |  |  |  |  |20|9 |11|  |12|  |"
# define GOTO_6  "|  |  |  |  |  |  |21|  |  |22|11|  |12|  |"
# define GOTO_7  "|  |  |  |  |  |  |  |23|  |24|11|  |12|  |"
# define GOTO_8  "|  |26|2 |3 |5 |4 |7 |  |6 |9 |11|  |12|  |"
# define GOTO_9  "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_10 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_11 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_12 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_13 "|  |  |  |  |  |  |  |  |  |  |  |27|  |  |"
# define GOTO_14 "|  |  |  |  |  |  |  |  |  |  |  |29|  |  |"
# define GOTO_15 "|  |  |  |  |  |  |  |  |  |  |  |30|  |  |"
# define GOTO_16 "|  |  |  |  |  |  |  |  |  |  |  |  |  |31|"
# define GOTO_17 "|  |  |33|3 |5 |4 |7 |  |6 |9 |11|  |12|  |"
# define GOTO_18 "|  |  |34|3 |5 |4 |7 |  |6 |9 |11|  |12|  |"
# define GOTO_19 "|  |  |  |35|5 |4 |7 |  |6 |9 |11|  |12|  |"
# define GOTO_20 "|  |  |  |  |  |  |  |  |  |22|11|  |12|  |"
# define GOTO_21 "|  |  |  |  |  |  |  |36|  |24|11|  |12|  |"
# define GOTO_22 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_23 "|  |  |  |  |  |  |  |  |  |37|11|  |12|  |"
# define GOTO_24 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_25 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_26 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_27 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_28 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_29 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_30 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_31 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_32 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_33 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_34 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_35 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_36 "|  |  |  |  |  |  |  |  |  |37|11|  |12|  |"
# define GOTO_37 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_38 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"
# define GOTO_39 "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |"

#endif