;; Enrico Scala (enricos83@gmail.com) and Miquel Ramirez (miquel.ramirez@gmail.com)
(define (problem pfile13)
(:domain TPP-Metric)
(:objects
	market1 market2 market3 market4 market5 market6 market7 market8 market9 market10 market11 market12 market13 market14 market15 - market
	depot0 - depot
	truck0 - truck
	goods0 goods1 goods2 goods3 goods4 goods5 goods6 goods7 goods8 goods9 goods10 goods11 goods12 - goods)
(:init
	(= (price goods1 market1) 41)
	(= (on-sale goods1 market1) 3)
	(= (price goods2 market1) 28)
	(= (on-sale goods2 market1) 10)
	(= (price goods5 market1) 8)
	(= (on-sale goods5 market1) 1)
	(= (price goods6 market1) 18)
	(= (on-sale goods6 market1) 9)
	(= (price goods7 market1) 25)
	(= (on-sale goods7 market1) 1)
	(= (price goods9 market1) 30)
	(= (on-sale goods9 market1) 5)
	(= (price goods10 market1) 9)
	(= (on-sale goods10 market1) 20)
	(= (price goods11 market1) 7)
	(= (on-sale goods11 market1) 16)
	(= (on-sale goods0 market1) 0)
	(= (on-sale goods3 market1) 0)
	(= (on-sale goods4 market1) 0)
	(= (on-sale goods8 market1) 0)
	(= (on-sale goods12 market1) 0)
	(= (price goods5 market2) 33)
	(= (on-sale goods5 market2) 13)
	(= (price goods6 market2) 29)
	(= (on-sale goods6 market2) 20)
	(= (price goods7 market2) 26)
	(= (on-sale goods7 market2) 8)
	(= (price goods8 market2) 45)
	(= (on-sale goods8 market2) 7)
	(= (price goods9 market2) 34)
	(= (on-sale goods9 market2) 15)
	(= (price goods10 market2) 21)
	(= (on-sale goods10 market2) 6)
	(= (on-sale goods0 market2) 0)
	(= (on-sale goods1 market2) 0)
	(= (on-sale goods2 market2) 0)
	(= (on-sale goods3 market2) 0)
	(= (on-sale goods4 market2) 0)
	(= (on-sale goods11 market2) 0)
	(= (on-sale goods12 market2) 0)
	(= (price goods0 market3) 38)
	(= (on-sale goods0 market3) 5)
	(= (price goods1 market3) 49)
	(= (on-sale goods1 market3) 6)
	(= (price goods3 market3) 50)
	(= (on-sale goods3 market3) 11)
	(= (price goods9 market3) 6)
	(= (on-sale goods9 market3) 4)
	(= (price goods10 market3) 11)
	(= (on-sale goods10 market3) 13)
	(= (price goods11 market3) 44)
	(= (on-sale goods11 market3) 15)
	(= (on-sale goods2 market3) 0)
	(= (on-sale goods4 market3) 0)
	(= (on-sale goods5 market3) 0)
	(= (on-sale goods6 market3) 0)
	(= (on-sale goods7 market3) 0)
	(= (on-sale goods8 market3) 0)
	(= (on-sale goods12 market3) 0)
	(= (price goods0 market4) 14)
	(= (on-sale goods0 market4) 12)
	(= (price goods1 market4) 17)
	(= (on-sale goods1 market4) 2)
	(= (price goods6 market4) 12)
	(= (on-sale goods6 market4) 7)
	(= (price goods7 market4) 25)
	(= (on-sale goods7 market4) 15)
	(= (price goods9 market4) 16)
	(= (on-sale goods9 market4) 9)
	(= (on-sale goods2 market4) 0)
	(= (on-sale goods3 market4) 0)
	(= (on-sale goods4 market4) 0)
	(= (on-sale goods5 market4) 0)
	(= (on-sale goods8 market4) 0)
	(= (on-sale goods10 market4) 0)
	(= (on-sale goods11 market4) 0)
	(= (on-sale goods12 market4) 0)
	(= (price goods1 market5) 11)
	(= (on-sale goods1 market5) 2)
	(= (price goods2 market5) 40)
	(= (on-sale goods2 market5) 4)
	(= (price goods6 market5) 29)
	(= (on-sale goods6 market5) 3)
	(= (price goods10 market5) 48)
	(= (on-sale goods10 market5) 12)
	(= (price goods11 market5) 37)
	(= (on-sale goods11 market5) 12)
	(= (price goods12 market5) 21)
	(= (on-sale goods12 market5) 20)
	(= (on-sale goods0 market5) 0)
	(= (on-sale goods3 market5) 0)
	(= (on-sale goods4 market5) 0)
	(= (on-sale goods5 market5) 0)
	(= (on-sale goods7 market5) 0)
	(= (on-sale goods8 market5) 0)
	(= (on-sale goods9 market5) 0)
	(= (price goods2 market6) 41)
	(= (on-sale goods2 market6) 20)
	(= (price goods3 market6) 16)
	(= (on-sale goods3 market6) 11)
	(= (price goods4 market6) 28)
	(= (on-sale goods4 market6) 18)
	(= (price goods6 market6) 8)
	(= (on-sale goods6 market6) 20)
	(= (price goods7 market6) 40)
	(= (on-sale goods7 market6) 14)
	(= (price goods9 market6) 10)
	(= (on-sale goods9 market6) 18)
	(= (price goods10 market6) 19)
	(= (on-sale goods10 market6) 6)
	(= (on-sale goods0 market6) 0)
	(= (on-sale goods1 market6) 0)
	(= (on-sale goods5 market6) 0)
	(= (on-sale goods8 market6) 0)
	(= (on-sale goods11 market6) 0)
	(= (on-sale goods12 market6) 0)
	(= (price goods1 market7) 48)
	(= (on-sale goods1 market7) 12)
	(= (price goods3 market7) 42)
	(= (on-sale goods3 market7) 1)
	(= (price goods8 market7) 49)
	(= (on-sale goods8 market7) 5)
	(= (price goods10 market7) 23)
	(= (on-sale goods10 market7) 9)
	(= (price goods11 market7) 36)
	(= (on-sale goods11 market7) 9)
	(= (price goods12 market7) 34)
	(= (on-sale goods12 market7) 16)
	(= (on-sale goods0 market7) 0)
	(= (on-sale goods2 market7) 0)
	(= (on-sale goods4 market7) 0)
	(= (on-sale goods5 market7) 0)
	(= (on-sale goods6 market7) 0)
	(= (on-sale goods7 market7) 0)
	(= (on-sale goods9 market7) 0)
	(= (price goods0 market8) 44)
	(= (on-sale goods0 market8) 15)
	(= (price goods4 market8) 25)
	(= (on-sale goods4 market8) 6)
	(= (price goods6 market8) 32)
	(= (on-sale goods6 market8) 20)
	(= (price goods8 market8) 45)
	(= (on-sale goods8 market8) 7)
	(= (price goods9 market8) 33)
	(= (on-sale goods9 market8) 16)
	(= (on-sale goods1 market8) 0)
	(= (on-sale goods2 market8) 0)
	(= (on-sale goods3 market8) 0)
	(= (on-sale goods5 market8) 0)
	(= (on-sale goods7 market8) 0)
	(= (on-sale goods10 market8) 0)
	(= (on-sale goods11 market8) 0)
	(= (on-sale goods12 market8) 0)
	(= (price goods1 market9) 44)
	(= (on-sale goods1 market9) 16)
	(= (price goods3 market9) 40)
	(= (on-sale goods3 market9) 19)
	(= (price goods5 market9) 46)
	(= (on-sale goods5 market9) 10)
	(= (price goods7 market9) 11)
	(= (on-sale goods7 market9) 13)
	(= (price goods12 market9) 1)
	(= (on-sale goods12 market9) 11)
	(= (on-sale goods0 market9) 0)
	(= (on-sale goods2 market9) 0)
	(= (on-sale goods4 market9) 0)
	(= (on-sale goods6 market9) 0)
	(= (on-sale goods8 market9) 0)
	(= (on-sale goods9 market9) 0)
	(= (on-sale goods10 market9) 0)
	(= (on-sale goods11 market9) 0)
	(= (price goods1 market10) 22)
	(= (on-sale goods1 market10) 13)
	(= (price goods2 market10) 28)
	(= (on-sale goods2 market10) 16)
	(= (price goods6 market10) 11)
	(= (on-sale goods6 market10) 1)
	(= (price goods8 market10) 11)
	(= (on-sale goods8 market10) 17)
	(= (price goods9 market10) 9)
	(= (on-sale goods9 market10) 12)
	(= (price goods11 market10) 11)
	(= (on-sale goods11 market10) 20)
	(= (price goods12 market10) 49)
	(= (on-sale goods12 market10) 20)
	(= (on-sale goods0 market10) 0)
	(= (on-sale goods3 market10) 0)
	(= (on-sale goods4 market10) 0)
	(= (on-sale goods5 market10) 0)
	(= (on-sale goods7 market10) 0)
	(= (on-sale goods10 market10) 0)
	(= (price goods0 market11) 31)
	(= (on-sale goods0 market11) 20)
	(= (price goods3 market11) 1)
	(= (on-sale goods3 market11) 14)
	(= (price goods5 market11) 15)
	(= (on-sale goods5 market11) 10)
	(= (price goods6 market11) 8)
	(= (on-sale goods6 market11) 17)
	(= (price goods11 market11) 10)
	(= (on-sale goods11 market11) 4)
	(= (price goods12 market11) 6)
	(= (on-sale goods12 market11) 12)
	(= (on-sale goods1 market11) 0)
	(= (on-sale goods2 market11) 0)
	(= (on-sale goods4 market11) 0)
	(= (on-sale goods7 market11) 0)
	(= (on-sale goods8 market11) 0)
	(= (on-sale goods9 market11) 0)
	(= (on-sale goods10 market11) 0)
	(= (price goods0 market12) 19)
	(= (on-sale goods0 market12) 2)
	(= (price goods1 market12) 30)
	(= (on-sale goods1 market12) 11)
	(= (price goods4 market12) 4)
	(= (on-sale goods4 market12) 18)
	(= (price goods5 market12) 11)
	(= (on-sale goods5 market12) 4)
	(= (price goods6 market12) 30)
	(= (on-sale goods6 market12) 16)
	(= (price goods7 market12) 28)
	(= (on-sale goods7 market12) 10)
	(= (price goods10 market12) 48)
	(= (on-sale goods10 market12) 6)
	(= (price goods11 market12) 14)
	(= (on-sale goods11 market12) 3)
	(= (price goods12 market12) 21)
	(= (on-sale goods12 market12) 3)
	(= (on-sale goods2 market12) 0)
	(= (on-sale goods3 market12) 0)
	(= (on-sale goods8 market12) 0)
	(= (on-sale goods9 market12) 0)
	(= (price goods2 market13) 23)
	(= (on-sale goods2 market13) 2)
	(= (price goods5 market13) 45)
	(= (on-sale goods5 market13) 6)
	(= (price goods6 market13) 18)
	(= (on-sale goods6 market13) 10)
	(= (price goods7 market13) 5)
	(= (on-sale goods7 market13) 14)
	(= (price goods8 market13) 41)
	(= (on-sale goods8 market13) 20)
	(= (price goods11 market13) 7)
	(= (on-sale goods11 market13) 1)
	(= (price goods12 market13) 2)
	(= (on-sale goods12 market13) 16)
	(= (on-sale goods0 market13) 0)
	(= (on-sale goods1 market13) 0)
	(= (on-sale goods3 market13) 0)
	(= (on-sale goods4 market13) 0)
	(= (on-sale goods9 market13) 0)
	(= (on-sale goods10 market13) 0)
	(= (price goods0 market14) 3)
	(= (on-sale goods0 market14) 1)
	(= (price goods1 market14) 10)
	(= (on-sale goods1 market14) 4)
	(= (price goods2 market14) 25)
	(= (on-sale goods2 market14) 6)
	(= (price goods3 market14) 32)
	(= (on-sale goods3 market14) 10)
	(= (price goods4 market14) 20)
	(= (on-sale goods4 market14) 5)
	(= (price goods5 market14) 37)
	(= (on-sale goods5 market14) 2)
	(= (price goods7 market14) 40)
	(= (on-sale goods7 market14) 3)
	(= (price goods8 market14) 32)
	(= (on-sale goods8 market14) 18)
	(= (price goods9 market14) 35)
	(= (on-sale goods9 market14) 6)
	(= (price goods12 market14) 20)
	(= (on-sale goods12 market14) 5)
	(= (on-sale goods6 market14) 0)
	(= (on-sale goods10 market14) 0)
	(= (on-sale goods11 market14) 0)
	(= (price goods0 market15) 32)
	(= (on-sale goods0 market15) 6)
	(= (price goods1 market15) 49)
	(= (on-sale goods1 market15) 7)
	(= (price goods4 market15) 30)
	(= (on-sale goods4 market15) 14)
	(= (price goods5 market15) 42)
	(= (on-sale goods5 market15) 6)
	(= (price goods7 market15) 7)
	(= (on-sale goods7 market15) 8)
	(= (price goods8 market15) 50)
	(= (on-sale goods8 market15) 10)
	(= (price goods11 market15) 21)
	(= (on-sale goods11 market15) 15)
	(= (price goods12 market15) 12)
	(= (on-sale goods12 market15) 19)
	(= (on-sale goods2 market15) 0)
	(= (on-sale goods3 market15) 0)
	(= (on-sale goods6 market15) 0)
	(= (on-sale goods9 market15) 0)
	(= (on-sale goods10 market15) 0)
	(loc truck0 depot0)
	(= (drive-cost depot0 market1) 381.20)
	(= (drive-cost market1 depot0) 381.20)
	(= (drive-cost depot0 market2) 737.52)
	(= (drive-cost market2 depot0) 737.52)
	(= (drive-cost depot0 market3) 452.95)
	(= (drive-cost market3 depot0) 452.95)
	(= (drive-cost depot0 market4) 516.44)
	(= (drive-cost market4 depot0) 516.44)
	(= (drive-cost depot0 market5) 558.53)
	(= (drive-cost market5 depot0) 558.53)
	(= (drive-cost depot0 market6) 108.58)
	(= (drive-cost market6 depot0) 108.58)
	(= (drive-cost depot0 market7) 505.36)
	(= (drive-cost market7 depot0) 505.36)
	(= (drive-cost depot0 market8) 550.41)
	(= (drive-cost market8 depot0) 550.41)
	(= (drive-cost depot0 market9) 240.86)
	(= (drive-cost market9 depot0) 240.86)
	(= (drive-cost depot0 market10) 495.59)
	(= (drive-cost market10 depot0) 495.59)
	(= (drive-cost depot0 market11) 198.04)
	(= (drive-cost market11 depot0) 198.04)
	(= (drive-cost depot0 market12) 745.67)
	(= (drive-cost market12 depot0) 745.67)
	(= (drive-cost depot0 market13) 647.71)
	(= (drive-cost market13 depot0) 647.71)
	(= (drive-cost depot0 market14) 258.31)
	(= (drive-cost market14 depot0) 258.31)
	(= (drive-cost depot0 market15) 446.07)
	(= (drive-cost market15 depot0) 446.07)
	(= (drive-cost market1 market2) 1033.70)
	(= (drive-cost market2 market1) 1033.70)
	(= (drive-cost market1 market3) 227.66)
	(= (drive-cost market3 market1) 227.66)
	(= (drive-cost market1 market4) 175.31)
	(= (drive-cost market4 market1) 175.31)
	(= (drive-cost market1 market5) 458.57)
	(= (drive-cost market5 market1) 458.57)
	(= (drive-cost market1 market6) 481.77)
	(= (drive-cost market6 market1) 481.77)
	(= (drive-cost market1 market7) 212.51)
	(= (drive-cost market7 market1) 212.51)
	(= (drive-cost market1 market8) 827.23)
	(= (drive-cost market8 market1) 827.23)
	(= (drive-cost market1 market9) 163.69)
	(= (drive-cost market9 market1) 163.69)
	(= (drive-cost market1 market10) 145.50)
	(= (drive-cost market10 market1) 145.50)
	(= (drive-cost market1 market11) 279.21)
	(= (drive-cost market11 market1) 279.21)
	(= (drive-cost market1 market12) 875.20)
	(= (drive-cost market12 market1) 875.20)
	(= (drive-cost market1 market13) 388.63)
	(= (drive-cost market13 market1) 388.63)
	(= (drive-cost market1 market14) 189.71)
	(= (drive-cost market14 market1) 189.71)
	(= (drive-cost market1 market15) 70.01)
	(= (drive-cost market15 market1) 70.01)
	(= (drive-cost market2 market3) 944.03)
	(= (drive-cost market3 market2) 944.03)
	(= (drive-cost market2 market4) 1080.73)
	(= (drive-cost market4 market2) 1080.73)
	(= (drive-cost market2 market5) 826.28)
	(= (drive-cost market5 market2) 826.28)
	(= (drive-cost market2 market6) 638.60)
	(= (drive-cost market6 market2) 638.60)
	(= (drive-cost market2 market7) 1025.31)
	(= (drive-cost market7 market2) 1025.31)
	(= (drive-cost market2 market8) 208.06)
	(= (drive-cost market8 market2) 208.06)
	(= (drive-cost market2 market9) 871.85)
	(= (drive-cost market9 market2) 871.85)
	(= (drive-cost market2 market10) 1077.51)
	(= (drive-cost market10 market2) 1077.51)
	(= (drive-cost market2 market11) 935.42)
	(= (drive-cost market11 market2) 935.42)
	(= (drive-cost market2 market12) 457.03)
	(= (drive-cost market12 market2) 457.03)
	(= (drive-cost market2 market13) 1057.64)
	(= (drive-cost market13 market2) 1057.64)
	(= (drive-cost market2 market14) 983.10)
	(= (drive-cost market14 market2) 983.10)
	(= (drive-cost market2 market15) 1074.62)
	(= (drive-cost market15 market2) 1074.62)
	(= (drive-cost market3 market4) 146.54)
	(= (drive-cost market4 market3) 146.54)
	(= (drive-cost market3 market5) 237.45)
	(= (drive-cost market5 market3) 237.45)
	(= (drive-cost market3 market6) 522.61)
	(= (drive-cost market6 market3) 522.61)
	(= (drive-cost market3 market7) 81.47)
	(= (drive-cost market7 market3) 81.47)
	(= (drive-cost market3 market8) 737.35)
	(= (drive-cost market8 market3) 737.35)
	(= (drive-cost market3 market9) 227.18)
	(= (drive-cost market9 market3) 227.18)
	(= (drive-cost market3 market10) 156.31)
	(= (drive-cost market10 market3) 156.31)
	(= (drive-cost market3 market11) 445.73)
	(= (drive-cost market11 market3) 445.73)
	(= (drive-cost market3 market12) 700.46)
	(= (drive-cost market12 market3) 700.46)
	(= (drive-cost market3 market13) 196.73)
	(= (drive-cost market13 market3) 196.73)
	(= (drive-cost market3 market14) 378.99)
	(= (drive-cost market14 market3) 378.99)
	(= (drive-cost market3 market15) 206.00)
	(= (drive-cost market15 market3) 206.00)
	(= (drive-cost market4 market5) 370.71)
	(= (drive-cost market5 market4) 370.71)
	(= (drive-cost market4 market6) 604.20)
	(= (drive-cost market6 market4) 604.20)
	(= (drive-cost market4 market7) 74.06)
	(= (drive-cost market7 market4) 74.06)
	(= (drive-cost market4 market8) 872.98)
	(= (drive-cost market8 market4) 872.98)
	(= (drive-cost market4 market9) 275.75)
	(= (drive-cost market9 market4) 275.75)
	(= (drive-cost market4 market10) 30.81)
	(= (drive-cost market10 market4) 30.81)
	(= (drive-cost market4 market11) 449.72)
	(= (drive-cost market11 market4) 449.72)
	(= (drive-cost market4 market12) 846.57)
	(= (drive-cost market12 market4) 846.57)
	(= (drive-cost market4 market13) 228.66)
	(= (drive-cost market13 market4) 228.66)
	(= (drive-cost market4 market14) 363.72)
	(= (drive-cost market14 market4) 363.72)
	(= (drive-cost market4 market15) 114.40)
	(= (drive-cost market15 market4) 114.40)
	(= (drive-cost market5 market6) 587.93)
	(= (drive-cost market6 market5) 587.93)
	(= (drive-cost market5 market7) 296.67)
	(= (drive-cost market7 market5) 296.67)
	(= (drive-cost market5 market8) 633.55)
	(= (drive-cost market8 market5) 633.55)
	(= (drive-cost market5 market9) 399.51)
	(= (drive-cost market9 market5) 399.51)
	(= (drive-cost market5 market10) 388.01)
	(= (drive-cost market10 market5) 388.01)
	(= (drive-cost market5 market11) 623.10)
	(= (drive-cost market11 market5) 623.10)
	(= (drive-cost market5 market12) 498.76)
	(= (drive-cost market12 market5) 498.76)
	(= (drive-cost market5 market13) 241.23)
	(= (drive-cost market13 market5) 241.23)
	(= (drive-cost market5 market14) 578.29)
	(= (drive-cost market14 market5) 578.29)
	(= (drive-cost market5 market15) 443.40)
	(= (drive-cost market15 market5) 443.40)
	(= (drive-cost market6 market7) 583.98)
	(= (drive-cost market7 market6) 583.98)
	(= (drive-cost market6 market8) 460.43)
	(= (drive-cost market8 market6) 460.43)
	(= (drive-cost market6 market9) 330.55)
	(= (drive-cost market9 market6) 330.55)
	(= (drive-cost market6 market10) 586.04)
	(= (drive-cost market10 market6) 586.04)
	(= (drive-cost market6 market11) 302.33)
	(= (drive-cost market11 market6) 302.33)
	(= (drive-cost market6 market12) 695.01)
	(= (drive-cost market12 market6) 695.01)
	(= (drive-cost market6 market13) 711.07)
	(= (drive-cost market13 market6) 711.07)
	(= (drive-cost market6 market14) 366.86)
	(= (drive-cost market14 market6) 366.86)
	(= (drive-cost market6 market15) 543.81)
	(= (drive-cost market15 market6) 543.81)
	(= (drive-cost market7 market8) 818.46)
	(= (drive-cost market8 market7) 818.46)
	(= (drive-cost market7 market9) 267.61)
	(= (drive-cost market9 market7) 267.61)
	(= (drive-cost market7 market10) 94.59)
	(= (drive-cost market10 market7) 94.59)
	(= (drive-cost market7 market11) 467.82)
	(= (drive-cost market11 market7) 467.82)
	(= (drive-cost market7 market12) 775.87)
	(= (drive-cost market12 market7) 775.87)
	(= (drive-cost market7 market13) 176.18)
	(= (drive-cost market13 market7) 176.18)
	(= (drive-cost market7 market14) 389.65)
	(= (drive-cost market14 market7) 389.65)
	(= (drive-cost market7 market15) 167.59)
	(= (drive-cost market15 market7) 167.59)
	(= (drive-cost market8 market9) 666.32)
	(= (drive-cost market9 market8) 666.32)
	(= (drive-cost market8 market10) 869.51)
	(= (drive-cost market10 market8) 869.51)
	(= (drive-cost market8 market11) 745.93)
	(= (drive-cost market11 market8) 745.93)
	(= (drive-cost market8 market12) 363.59)
	(= (drive-cost market12 market8) 363.59)
	(= (drive-cost market8 market13) 858.41)
	(= (drive-cost market13 market8) 858.41)
	(= (drive-cost market8 market14) 786.15)
	(= (drive-cost market14 market8) 786.15)
	(= (drive-cost market8 market15) 866.98)
	(= (drive-cost market15 market8) 866.98)
	(= (drive-cost market9 market10) 255.93)
	(= (drive-cost market10 market9) 255.93)
	(= (drive-cost market9 market11) 226.06)
	(= (drive-cost market11 market9) 226.06)
	(= (drive-cost market9 market12) 745.01)
	(= (drive-cost market12 market9) 745.01)
	(= (drive-cost market9 market13) 423.45)
	(= (drive-cost market13 market9) 423.45)
	(= (drive-cost market9 market14) 182.08)
	(= (drive-cost market14 market9) 182.08)
	(= (drive-cost market9 market15) 216.93)
	(= (drive-cost market15 market9) 216.93)
	(= (drive-cost market10 market11) 421.72)
	(= (drive-cost market11 market10) 421.72)
	(= (drive-cost market10 market12) 856.02)
	(= (drive-cost market12 market10) 856.02)
	(= (drive-cost market10 market13) 258.03)
	(= (drive-cost market13 market10) 258.03)
	(= (drive-cost market10 market14) 334.61)
	(= (drive-cost market14 market10) 334.61)
	(= (drive-cost market10 market15) 83.60)
	(= (drive-cost market15 market10) 83.60)
	(= (drive-cost market11 market12) 909.28)
	(= (drive-cost market12 market11) 909.28)
	(= (drive-cost market11 market13) 637.31)
	(= (drive-cost market13 market11) 637.31)
	(= (drive-cost market11 market14) 94.37)
	(= (drive-cost market14 market11) 94.37)
	(= (drive-cost market11 market15) 348.90)
	(= (drive-cost market15 market11) 348.90)
	(= (drive-cost market12 market13) 737.48)
	(= (drive-cost market13 market12) 737.48)
	(= (drive-cost market12 market14) 912.92)
	(= (drive-cost market14 market12) 912.92)
	(= (drive-cost market12 market15) 887.85)
	(= (drive-cost market15 market12) 887.85)
	(= (drive-cost market13 market14) 563.40)
	(= (drive-cost market14 market13) 563.40)
	(= (drive-cost market13 market15) 339.32)
	(= (drive-cost market15 market13) 339.32)
	(= (drive-cost market14 market15) 258.28)
	(= (drive-cost market15 market14) 258.28)
	(= (bought goods0) 0)
	(= (request goods0) 9)
	(= (bought goods1) 0)
	(= (request goods1) 48)
	(= (bought goods2) 0)
	(= (request goods2) 14)
	(= (bought goods3) 0)
	(= (request goods3) 33)
	(= (bought goods4) 0)
	(= (request goods4) 44)
	(= (bought goods5) 0)
	(= (request goods5) 16)
	(= (bought goods6) 0)
	(= (request goods6) 43)
	(= (bought goods7) 0)
	(= (request goods7) 2)
	(= (bought goods8) 0)
	(= (request goods8) 50)
	(= (bought goods9) 0)
	(= (request goods9) 17)
	(= (bought goods10) 0)
	(= (request goods10) 58)
	(= (bought goods11) 0)
	(= (request goods11) 13)
	(= (bought goods12) 0)
	(= (request goods12) 38)
	(= (total-cost) 0))

(:goal (and
	(>= (bought goods0) (request goods0))
	(>= (bought goods1) (request goods1))
	(>= (bought goods2) (request goods2))
	(>= (bought goods3) (request goods3))
	(>= (bought goods4) (request goods4))
	(>= (bought goods5) (request goods5))
	(>= (bought goods6) (request goods6))
	(>= (bought goods7) (request goods7))
	(>= (bought goods8) (request goods8))
	(>= (bought goods9) (request goods9))
	(>= (bought goods10) (request goods10))
	(>= (bought goods11) (request goods11))
	(>= (bought goods12) (request goods12))
	(loc truck0 depot0)))

)