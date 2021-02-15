; ModuleID = 'input.c'
source_filename = "input.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo() #0 {
entry:
  %ptr = alloca i32*, align 8
  %x = alloca i32, align 4
  store i32 100, i32* %x, align 4
  store i32* %x, i32** %ptr, align 8
  %0 = load i32*, i32** %ptr, align 8
  %1 = load i32, i32* %0, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @bar() #0 {
entry:
  %p = alloca i32*, align 8
  %q = alloca i32*, align 8
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 100, i32* %a, align 4
  store i32 200, i32* %b, align 4
  store i32* %a, i32** %p, align 8
  store i32* %b, i32** %q, align 8
  %0 = load i32*, i32** %q, align 8
  store i32* %0, i32** %p, align 8
  %1 = load i32*, i32** %p, align 8
  %2 = load i32, i32* %1, align 4
  ret i32 %2
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %call = call i32 @foo()
  %call1 = call i32 @bar()
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0 (https://github.com/llvm/llvm-project.git d32170dbd5b0d54436537b6b75beaf44324e0c28)"}
