@_fint = constant [4 x i8] c"%d\0a\00"
declare i8* @calloc(i32,i32)
declare i32 @printf(i8*,...)
declare void @exit(i32)
define void @main(i8* %a){
%1 = call i8* @calloc(i32 4, i32 1)
%2 = bitcast i8* %1 to i8***
%3 = call i8* @calloc(i32 4,i32 1)
%4 = bitcast i8* %3 to i8**
store i8** %4, i8*** %2
%5 = getelementptr i8*,i8** %4,i32 0
store i8* bitcast (i32 (i8*,i32)* @Fac_ComputeFac to i8*),i8** %5
%6 = bitcast i8* %1 to i8***
%7 = load i8**,i8*** %6
%8 = getelementptr i8*,i8** %7,i32 0
%9 = load i8*,i8** %8
%10 = bitcast i8* %9 to i32 (i8*,i32)*
%11 = add i32 10,0
%12 = call i32 %10(i8* %1,i32 %11)
%13 = bitcast [4 x i8]* @_fint to i8*
%14 = call i32 (i8*,...) @printf(i8* %13,i32 %12)
ret void
}
define i32 @Fac_ComputeFac (i8* %this,i32 %.num){
%num = alloca i32
store i32 %.num,i32* %num
%num_aux = alloca i32
%1 = load i32,i32* %num
%2 = icmp sle i32 %1,1
%3 = zext i1 %2 to i8
%4 = load i32,i32* %num
%5 = icmp ne i32 %4,1
%6 = zext i1 %5 to i8
%7 = and i8 %3,%6
%8 = trunc i8 %7 to i1
br i1 %8, label %L0,label %L1
L0:
%9 = add i32 1,0
store i32 %9,i32* %num_aux
br label %L2
L1:
%10 = load i32,i32* %num
%11 = bitcast i8* %this to i8***
%12 = load i8**,i8*** %11
%13 = getelementptr i8*,i8** %12,i32 0
%14 = load i8*,i8** %13
%15 = bitcast i8* %14 to i32 (i8*,i32)*
%16 = load i32,i32* %num
%17 = sub i32 %16,1
%18 = call i32 %15(i8* %this,i32 %17)
%19 = mul i32 %10,%18
store i32 %19,i32* %num_aux
br label %L2
L2:
%20 = add i32 0,0
%21 = load i32,i32* %num_aux
ret i32 %21
}
