_n='div'
_m='times'
_l='Pof'
_k='MCp'
_j='negm'
_i='invd'
_h='nega'
_g='invs'
_f='min'
_e='max'
_d='mshd'
_c='mshs'
_b='enshd'
_a='enshs'
_Z='aeg'
_Y='amg'
_X='amd'
_W='tns'
_V='msin'
_U='mson'
_T='tms'
_S='esin'
_R='eson'
_Q='tes'
_P='nnp'
_O='nep'
_N='nmp'
_M='dns'
_L='sns'
_K='dsd'
_J='pdie'
_I='pdin'
_H='pdim'
_G='nsim'
_F=','
_E='}'
_D='{'
_C='{}'
_B=0.0
_A=None
import os,sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__),'../..')))
from time import sleep
from threading import Thread,active_count
from collections import defaultdict
from PlanetWars import PlanetWars,Planet,Fleet
from math import ceil
from random import shuffle,choice,random,randint
from Log import game_log
from enum import Enum,auto
class CashSucks(Enum):p2E=auto();one=auto();nsimo=auto();pdimi=auto();pdN=auto();pdE=auto();DsD=auto();Gso=auto();Gde=auto();SnS=auto();DnS=auto();Mp=auto();Ep=auto();nP=auto();Qt=auto();bwE=auto();LMw=auto();Wos=auto();PfS=auto();Juy=auto();REi=auto();ApT=auto();amG=auto();aeG=auto();IOc=auto();CKs=auto();LOw=auto();DickCheese=auto();LeU=auto();Qrs=auto();TaL=auto();Btn=auto();PoW=auto();WeX=auto();FaT=auto();Ok=auto();SoA=auto();MCp=auto();Pof=auto();WlA=auto();MoS=auto();TpE=auto()
def STE(string):
	A=string
	if A=='1':return CashSucks.one
	if A==_G:return CashSucks.nsimo
	if A==_H:return CashSucks.pdimi
	if A==_I:return CashSucks.pdN
	if A==_J:return CashSucks.pdE
	if A==_K:return CashSucks.DsD
	if A=='gs':return CashSucks.Gso
	if A=='gd':return CashSucks.Gde
	if A==_L:return CashSucks.SnS
	if A==_M:return CashSucks.DnS
	if A==_N:return CashSucks.Mp
	if A==_O:return CashSucks.Ep
	if A==_P:return CashSucks.nP
	if A==_Q:return CashSucks.Qt
	if A==_R:return CashSucks.bwE
	if A==_S:return CashSucks.LMw
	if A==_T:return CashSucks.Wos
	if A==_U:return CashSucks.PfS
	if A==_V:return CashSucks.Juy
	if A==_W:return CashSucks.REi
	if A==_X:return CashSucks.ApT
	if A==_Y:return CashSucks.amG
	if A==_Z:return CashSucks.aeG
	if A==_a:return CashSucks.IOc
	if A==_b:return CashSucks.CKs
	if A==_c:return CashSucks.LOw
	if A==_d:return CashSucks.DickCheese
	if A==_e:return CashSucks.Qrs
	if A==_f:return CashSucks.TaL
	if A==_g:return CashSucks.Btn
	if A==_h:return CashSucks.PoW
	if A==_i:return CashSucks.WeX
	if A==_j:return CashSucks.FaT
	if A=='lt':return CashSucks.Ok
	if A=='gt':return CashSucks.SoA
	if A==_k:return CashSucks.MCp
	if A==_l:return CashSucks.Pof
	if A==_m:return CashSucks.WlA
	if A==_n:return CashSucks.MoS
def EnumTS(node_value):
	A=node_value
	if A==CashSucks.one:return'1'
	if A==CashSucks.nsimo:return _G
	if A==CashSucks.pdimi:return _H
	if A==CashSucks.pdN:return _I
	if A==CashSucks.pdE:return _J
	if A==CashSucks.DsD:return _K
	if A==CashSucks.Gso:return'gs'
	if A==CashSucks.Gde:return'gd'
	if A==CashSucks.SnS:return _L
	if A==CashSucks.DnS:return _M
	if A==CashSucks.Mp:return _N
	if A==CashSucks.Ep:return _O
	if A==CashSucks.nP:return _P
	if A==CashSucks.Qt:return _Q
	if A==CashSucks.bwE:return _R
	if A==CashSucks.LMw:return _S
	if A==CashSucks.Wos:return _T
	if A==CashSucks.PfS:return _U
	if A==CashSucks.Juy:return _V
	if A==CashSucks.REi:return _W
	if A==CashSucks.ApT:return _X
	if A==CashSucks.amG:return _Y
	if A==CashSucks.aeG:return _Z
	if A==CashSucks.IOc:return _a
	if A==CashSucks.CKs:return _b
	if A==CashSucks.LOw:return _c
	if A==CashSucks.DickCheese:return _d
	if A==CashSucks.Qrs:return _e
	if A==CashSucks.TaL:return _f
	if A==CashSucks.Btn:return _g
	if A==CashSucks.PoW:return _h
	if A==CashSucks.WeX:return _i
	if A==CashSucks.FaT:return _j
	if A==CashSucks.Ok:return'lt'
	if A==CashSucks.SoA:return'gt'
	if A==CashSucks.MCp:return _k
	if A==CashSucks.Pof:return _l
	if A==CashSucks.WlA:return _m
	if A==CashSucks.MoS:return _n
def FSTAV(Set):
	A=Set;B=1;C=1
	while C>0 and B<len(A):
		if A[B]==_D:C+=1
		if A[B]==_E:C-=1
		B+=1
		if C==0:break
	D=A[B+1:len(A)].find(_F)+B+1;return A[0:B],A[D+1:len(A)],A[B+1:D]
def DTGT(Set):
	A=Set;A=A.rstrip()
	if A==_C:return _A
	B,C,D=FSTAV(A[1:len(A)-1])
	return GT(DTGT(B),DTGT(C),STE(D),iPQ=B==_C)
class GT:
	def __init__(A,lP=_A,lpEE=_A,value=CashSucks.one,iPQ=True):A.lP=lP;A.lpEE=lpEE;A.value=value;A.iPQ=iPQ
	def Enc(A):B=A.lP.Enc()if A.lP is not _A else _C;C=A.lpEE.Enc()if A.lpEE is not _A else _C;return _D+B+_F+EnumTS(A.value)+_F+C+_E
	def TS(E):
		F='  ';C=[E];A=''
		while len(C)>0:
			A+='\n';D=[]
			for B in C:
				if B is _A:continue
				A+=F;A+=_D if B.iPQ else'';A+=EnumTS(B.value);A+=_E if B.iPQ else'';A+=F;D.append(B.lP);D.append(B.lpEE)
			C=D
		return A
	def RN(A):B=A.GAN();return choice(B)
	def SRNS(C,other_t):A=C.RN();B=other_t.RN();D=A.lP;E=A.lpEE;F=A.value;G=A.iPQ;A.lP=B.lP;A.lpEE=B.lpEE;A.value=B.value;A.iPQ=B.iPQ;B.lP=D;B.lpEE=E;B.value=F;B.iPQ=G;return
	def CP(A):B=A.lP.CP()if A.lP is not _A else _A;C=A.lpEE.CP()if A.lpEE is not _A else _A;return GT(B,C,A.value,iPQ=A.iPQ)
	def GAN(A):
		B=[];B.append(A)
		if A.lP is not _A:
			B.append(A.lP);D=A.lP.GAN()
			for C in D:B.append(C)
		if A.lpEE is not _A:
			B.append(A.lpEE);E=A.lpEE.GAN()
			for C in E:B.append(C)
		return B
	def POW(A,LeU):B=A.CP();A.value=LeU;A.iPQ=False;A.lP=B.CP();A.lpEE=B
	def RNC(A):
		C=random();B=_A
		if C>0.5:B=A.lP
		else:B=A.lpEE
		A.value=B.value;A.lP=B.lP;A.lpEE=B.lpEE;A.iPQ=B.iPQ
	def RM(D):
		E=D.GAN();A=choice(E);F=CashSucks(randint(CashSucks.p2E.value+1,CashSucks.LeU.value-1));B=CashSucks(randint(CashSucks.LeU.value+1,CashSucks.TpE.value-1));C=random()
		if A.iPQ:
			if C>0.5:A.POW(B)
			else:A.value=F
		elif C<0.33:A.POW(B)
		elif C>0.66:A.value=B
		else:A.RNC()
		return D
class ES:
	def __init__(A):A.Qt=_A;A.Wos=_A;A.REi=_A;A.bwE=_A;A.LMw=_A;A.PfS=_A;A.Juy=_A;A.ApT=_A;A.amG=_A;A.aeG=_A;A.loG=_A;A.loR=_A
class MV:
	def __init__(A,se,dE,nS,pWi):A.se=se;A.dE=dE;A.nS=nS;A.pWi=pWi
class ESt:
	def __init__(A,t,plW,mK):A.t=t;A.plW=plW;A.mK=mK
def SS(t_state):
	I=t_state;B=1.0;C=I.mK;E=C.pWi;A=I.t.value;D=I.plW;H=C.dE;J=C.se;F=I.t.lP;G=I.t.lpEE
	if A==CashSucks.one:return B
	if A==CashSucks.nsimo:return C.nS*B
	if A==CashSucks.pdimi:return B if H.Owner()==B else _B
	if A==CashSucks.pdN:return B if H.Owner()==_B else _B
	if A==CashSucks.pdE:return B if H.Owner()>B else _B
	if A==CashSucks.DsD:return D.Distance(J,H)
	if A==CashSucks.Gso:return J.GrowthRate()*B
	if A==CashSucks.Gde:return H.GrowthRate()*B
	if A==CashSucks.SnS:return J.NumShips()*B
	if A==CashSucks.DnS:return H.NumShips()*B
	if A==CashSucks.Mp:return len(D.MyPlanets())*B
	if A==CashSucks.Ep:return len(D.EnemyPlanets())*B
	if A==CashSucks.nP:return len(D.NeutralPlanets())*B
	if A==CashSucks.Qt:return E.Qt*B
	if A==CashSucks.bwE:return E.bwE*B
	if A==CashSucks.LMw:return E.LMw*B
	if A==CashSucks.Wos:return E.Wos*B
	if A==CashSucks.PfS:return E.PfS*B
	if A==CashSucks.Juy:return E.Juy*B
	if A==CashSucks.REi:return E.REi*B
	if A==CashSucks.ApT:return E.ApT*B
	if A==CashSucks.amG:return E.amG*B
	if A==CashSucks.aeG:return E.aeG*B
	if A==CashSucks.IOc:return E.loR[J.PlanetID()]*B
	if A==CashSucks.CKs:return E.loR[H.PlanetID()]*B
	if A==CashSucks.LOw:return E.loG[J.PlanetID()]*B
	if A==CashSucks.DickCheese:return E.loG[H.PlanetID()]*B
	if A==CashSucks.Qrs:return max(SS(ESt(F,D,C)),SS(ESt(G,D,C)))
	if A==CashSucks.TaL:return min(SS(ESt(F,D,C)),SS(ESt(G,D,C)))
	if A==CashSucks.Btn:return SS(ESt(G,D,C))-SS(ESt(F,D,C))
	if A==CashSucks.PoW:return-B*SS(ESt(F,D,C))-B*SS(ESt(G,D,C))
	if A==CashSucks.WeX:K=SS(ESt(G,D,C))*B;L=SS(ESt(F,D,C))*B;return K if L==_B else K/L
	if A==CashSucks.FaT:return-B*SS(ESt(F,D,C))*SS(ESt(G,D,C))
	if A==CashSucks.Ok:return 1 if SS(ESt(F,D,C))<SS(ESt(G,D,C))else 0
	if A==CashSucks.SoA:return 1 if SS(ESt(F,D,C))>SS(ESt(G,D,C))else 0
	if A==CashSucks.MCp:return SS(ESt(F,D,C))+SS(ESt(G,D,C))
	if A==CashSucks.Pof:return SS(ESt(F,D,C))-SS(ESt(G,D,C))
	if A==CashSucks.WlA:return SS(ESt(F,D,C))*SS(ESt(G,D,C))
	if A==CashSucks.MoS:K=SS(ESt(F,D,C))*B;L=SS(ESt(G,D,C))*B;return K if L==_B else K/L
def GAPMV(plW,io2=_A):
	F=io2;D=plW;G=[];A=ES();A.Wos=0;A.Qt=0;A.REi=0;A.Juy=0;A.LMw=0;A.loG=defaultdict(int);A.loR=defaultdict(int)
	for B in D.Fleets():
		if B.Owner()==1:A.loG[B.DestinationPlanet()]+=B.NumShips();A.Wos+=B.NumShips();A.Juy+=B.NumShips()
		else:A.loR[B.DestinationPlanet()]+=B.NumShips();A.Qt+=B.NumShips();A.LMw+=B.NumShips()
	A.bwE=0;H=[]
	for E in D.EnemyPlanets():A.bwE+=E.NumShips();A.Qt+=E.NumShips();H.append(E.GrowthRate())
	for E in D.NeutralPlanets():A.REi+=E.NumShips()
	I=[];J=[];A.PfS=0
	if F is not _A:
		for K in F:G.append(MV(K.se,K.dE,K.nS,A))
	for C in D.MyPlanets():
		J.append(C.GrowthRate());A.PfS+=C.NumShips();A.Wos+=C.NumShips()
		for L in D.Planets():
			I.append(D.Distance(C,L))
			if F is _A:
				if C==L:continue
				st=int(ceil(A.Wos/15))
				while C.NumShips()>=st:G.append(MV(C,L,st,A));st*=3
	P=_B
	for S in I:P+=S/len(I)
	A.ApT=P;Q=_B
	for N in J:Q+=N/len(J)
	A.amG=Q;R=_B
	for N in H:R+=N/len(H)
	A.aeG=R;return G
def ScMV(plW,t,mK):return SS(ESt(t,plW,mK))
def ScMVUS(plW,t,mK,scores):scores[mK]=ScMV(plW,t,mK)
def DTu(pw,t):
	D=0;A=GAPMV(pw)
	while D<10:
		shuffle(A);print(str(len(A)));C={}
		for B in A:ScMVUS(pw,t,B,C)
		if len(C)==0:return
		E=list(C.items());F=max(E,key=lambda x:x[1])
		if F[1]<1e-06:return
		B=F[0];D+=1;pw.IssueOrder(B.se,B.dE,B.nS);A=[A[0]for A in E if A[1]>_B and A[0].se.NumShips()>=A[0].nS];A=GAPMV(pw,io2=A)
def main():
	A='';D='{{{{},dns,{}},invs,{{{{{{},tms,{}},MCp,{{},pdie,{}}},invd,{{{},tms,{}},MCp,{{},pdie,{}}}},times,{{{{},nsim,{}},times,{{{},enshd,{}},MCp,{{{},pdin,{}},MCp,{{},pdie,{}}}}},min,{{{},nsim,{}},Pof,{{{{{},tms,{}},MCp,{{{},pdie,{}},MCp,{{},pdie,{}}}},invd,{{{},tms,{}},max,{{{},pdie,{}},invd,{{},pdie,{}}}}},max,{{{{},tms,{}},MCp,{{{},pdie,{}},MCp,{{},pdie,{}}}},invd,{{{},tms,{}},max,{{{},pdie,{}},invd,{{},pdie,{}}}}}}}}},MCp,{{{{{},tms,{}},MCp,{{},tms,{}}},invd,{{{{},tms,{}},max,{{},dsd,{}}},MCp,{{},pdie,{}}}},times,{{{{},nsim,{}},times,{{{},nsim,{}},times,{{{},enshd,{}},MCp,{{{},pdin,{}},MCp,{{},pdie,{}}}}}},min,{{{},nsim,{}},Pof,{{{{{},dns,{}},invs,{{{{},tms,{}},invd,{{{},tms,{}},MCp,{{{},pdie,{}},invd,{{},pdie,{}}}}},times,{{{{},nsim,{}},times,{{{{},nsim,{}},MCp,{{},gd,{}}},times,{{{{},enshd,{}},nega,{{},enshd,{}}},div,{{{},pdin,{}},MCp,{{},enshd,{}}}}}},min,{{{},nsim,{}},Pof,{{{{},nsim,{}},nega,{{{{{{{},nsim,{}},MCp,{{},gd,{}}},times,{{{},nsim,{}},MCp,{{},gd,{}}}},invd,{{{{},nsim,{}},gt,{{},nsim,{}}},invd,{{{},tms,{}},max,{{{},tms,{}},MCp,{{},nsim,{}}}}}},gt,{{},nep,{}}},gt,{{{{{{},nsim,{}},MCp,{{},gd,{}}},times,{{{},nsim,{}},MCp,{{},gd,{}}}},invd,{{{{{{},nsim,{}},lt,{{},pdie,{}}},gt,{{},nsim,{}}},invd,{{{},tms,{}},max,{{{},tms,{}},MCp,{{},nsim,{}}}}},div,{{{{{},nsim,{}},lt,{{},pdie,{}}},gt,{{},nsim,{}}},invd,{{{},tms,{}},max,{{{},tms,{}},MCp,{{{{},nsim,{}},MCp,{{},enshd,{}}},invd,{{{{},nsim,{}},times,{{{},enshd,{}},MCp,{{{},pdin,{}},MCp,{{},pdie,{}}}}},invd,{{{},tms,{}},max,{{{},pdie,{}},invd,{{},pdie,{}}}}}}}}}}},gt,{{},nep,{}}}}},min,{{{{{},nsim,{}},MCp,{{},enshd,{}}},invd,{{{{},nsim,{}},times,{{{},enshd,{}},MCp,{{{},pdin,{}},MCp,{{},pdie,{}}}}},invd,{{{},tms,{}},max,{{{},pdie,{}},invd,{{},pdie,{}}}}}},lt,{{},nep,{}}}}}}}},lt,{{},nep,{}}},min,{{{},amg,{}},Pof,{{},nep,{}}}}}}}}},times,{{{},gd,{}},div,{{},dsd,{}}}}';E=DTGT(D)
	while True:
		B=input()
		if len(B)>=2 and B.startswith('go'):C=PlanetWars(A);DTu(C,E);C.FinishTurn();A=''
		else:A+=B+'\n'
if __name__=='__main__':
	try:import psyco;psyco.full()
	except ImportError:pass
	try:main()
	except KeyboardInterrupt:print('ctrl-c, leaving ...')
