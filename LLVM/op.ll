@.A_vtable = global [1 x i8*] [i8* bitcast (i32 (i8*)* @A.fun to i8*)]
@.T4_vtable = global [0 x i8*] []
declare i8* @calloc(i32, i32)
declare i32 @printf(i8*, ...)
declare void @exit(i32)
@_cint = constant [4 x i8] c"%d\0a\00"
@_cboolean = constant [4 x i8] c"%b\0a\00"
@_cOOB = constant [15 x i8] c"Out of bounds\0a\00"
define void @print_int(i32 %i){
%_0 = bitcast [4 x i8]* @_cint to i8*
%_1 = call i32 (i8*, ...) @printf(i8* %_0,i32 %i)
ret void
}
define void @print_bool(i1 %i){
%_0 = bitcast [4 x i8]* @_cboolean to i8*
%_1 = call i32 (i8*, ...) @printf(i8* %_0,i1 %i)
ret void
}
define void @throw_oob(){
%_0 = bitcast [15 x i8]* @_cOOB to i8*
call i32 (i8*, ...) @printf(i8* %_0)
call void @exit(i32 1)
ret void
}
define i32 @main(){
%_0 = call i8* @calloc(i32 1,i32 8)
%_1 = bitcast i8* %_0 to i8***
%_2 = getelementptr [1 x i8*],[1 x i8*]* @.A_vtable,i32 0,i32 0
store i8** %_2,i8*** %_1
%_3 = bitcast i8* %_0 to i8***
%_4 = load i8**,i8*** %_3
%_5 = getelementptr i8*,i8** %_4,i32 0
%_6 = load i8*,i8** %_5
%_7 = bitcast i8* %_6 to i32 (i8*)*
;A.fun : 0
%_8 = call i32 %_7(i8* %_0)
call void @print_int(i32 %_8)
ret i32 0
}
define i32 @A.fun(i8* %this){
%b = alloca i32
%a = alloca i32
%e = alloca i32
%d = alloca i32
%c = alloca i32
store i32 20, i32* %b
store i32 10, i32* %c
%_0 = load i32,i32* %b
%_1 = load i32,i32* %c
%_2 = sub i32 %_0,%_1
store i32 %_2, i32* %a
%_3 = load i32,i32* %b
%_4 = mul i32 %_3,4
store i32 %_4, i32* %d
%_5 = load i32,i32* %d
%_6 = load i32,i32* %a
%_7 = icmp sle i32 %_5,%_6
br i1 %_7, label %label0, label %label1
label0:
%_8 = add i32 0,0
%_9 = load i32,i32* %d
%_10 = load i32,i32* %c
%_11 = add i32 %_9,%_10
store i32 %_11, i32* %e
br label %label2
label1:
%_12 = add i32 0,0
%_13 = load i32,i32* %a
store i32 %_13, i32* %e
br label %label2
label2:
%_14 = add i32 0,0
%_15 = load i32,i32* %e
ret i32 %_15
}
