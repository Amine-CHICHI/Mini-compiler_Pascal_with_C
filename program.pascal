program test11;
const toto=21; titi=13;
var x,y;
Begin
{* initialisation de x *}
x:=toto;
read(y);
read(x);
while x<y do begin read(y); x:=x+y+titi end;
{* affichage des resultas
de x et y *}
write(x);
.