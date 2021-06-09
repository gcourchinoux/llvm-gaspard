; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.pagination_general_configuration = type { i32, i64 }
%struct.page_table = type { i16, [0 x %struct.page_child] }
%struct.page_child = type { i8, i8, i64 }
%struct.interrupt = type { i8, i64 }

@actuel_adress = dso_local global i64 4096, align 8
@pag_config = common dso_local global %struct.pagination_general_configuration* null, align 8
@pages = common dso_local global %struct.page_table* null, align 8
@.str = private unnamed_addr constant [13 x i8] c"prcfg PAG,%x\00", align 1
@chiara64_interrupt = common dso_local global %struct.interrupt* null, align 8
@.str.1 = private unnamed_addr constant [13 x i8] c"prcfg INT,%x\00", align 1
@.str.2 = private unnamed_addr constant [13 x i8] c"prcfg EXEC,2\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @get_next_virtual_adress(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %5 = load i64, i64* @actuel_adress, align 8
  store i64 %5, i64* %3, align 8
  store i32 0, i32* %4, align 4
  br label %6

; <label>:6:                                      ; preds = %14, %1
  %7 = load i32, i32* %4, align 4
  %8 = load i32, i32* %2, align 4
  %9 = sdiv i32 %8, 8
  %10 = icmp slt i32 %7, %9
  br i1 %10, label %11, label %17

; <label>:11:                                     ; preds = %6
  %12 = load i64, i64* @actuel_adress, align 8
  %13 = add i64 %12, 1
  store i64 %13, i64* @actuel_adress, align 8
  br label %14

; <label>:14:                                     ; preds = %11
  %15 = load i32, i32* %4, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* %4, align 4
  br label %6

; <label>:17:                                     ; preds = %6
  %18 = load i64, i64* %3, align 8
  ret i64 %18
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @init_pagination() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.page_child, align 8
  %3 = call i64 @get_next_virtual_adress(i32 16)
  %4 = inttoptr i64 %3 to %struct.pagination_general_configuration*
  store %struct.pagination_general_configuration* %4, %struct.pagination_general_configuration** @pag_config, align 8
  %5 = load %struct.pagination_general_configuration*, %struct.pagination_general_configuration** @pag_config, align 8
  %6 = bitcast %struct.pagination_general_configuration* %5 to i32*
  %7 = load i32, i32* %6, align 8
  %8 = and i32 %7, -65536
  %9 = or i32 %8, 20
  store i32 %9, i32* %6, align 8
  %10 = load %struct.pagination_general_configuration*, %struct.pagination_general_configuration** @pag_config, align 8
  %11 = bitcast %struct.pagination_general_configuration* %10 to i32*
  %12 = load i32, i32* %11, align 8
  %13 = and i32 %12, -16711681
  %14 = or i32 %13, 65536
  store i32 %14, i32* %11, align 8
  %15 = load %struct.pagination_general_configuration*, %struct.pagination_general_configuration** @pag_config, align 8
  %16 = bitcast %struct.pagination_general_configuration* %15 to i32*
  %17 = load i32, i32* %16, align 8
  %18 = and i32 %17, 16777215
  %19 = or i32 %18, 16777216
  store i32 %19, i32* %16, align 8
  %20 = call i64 @get_next_virtual_adress(i32 160)
  %21 = inttoptr i64 %20 to %struct.page_table*
  store %struct.page_table* %21, %struct.page_table** @pages, align 8
  %22 = load %struct.page_table*, %struct.page_table** @pages, align 8
  %23 = ptrtoint %struct.page_table* %22 to i64
  %24 = load %struct.pagination_general_configuration*, %struct.pagination_general_configuration** @pag_config, align 8
  %25 = getelementptr inbounds %struct.pagination_general_configuration, %struct.pagination_general_configuration* %24, i32 0, i32 1
  store i64 %23, i64* %25, align 8
  store i32 0, i32* %1, align 4
  br label %26

; <label>:26:                                     ; preds = %70, %0
  %27 = load i32, i32* %1, align 4
  %28 = icmp slt i32 %27, 20
  br i1 %28, label %29, label %73

; <label>:29:                                     ; preds = %26
  %30 = bitcast %struct.page_child* %2 to i8*
  %31 = load i8, i8* %30, align 8
  %32 = and i8 %31, -31
  %33 = or i8 %32, 6
  store i8 %33, i8* %30, align 8
  %34 = getelementptr inbounds %struct.page_child, %struct.page_child* %2, i32 0, i32 1
  %35 = load i8, i8* %34, align 1
  %36 = and i8 %35, -16
  store i8 %36, i8* %34, align 1
  %37 = call i64 @get_next_virtual_adress(i32 1)
  %38 = getelementptr inbounds %struct.page_child, %struct.page_child* %2, i32 0, i32 2
  store i64 %37, i64* %38, align 8
  %39 = load %struct.page_table*, %struct.page_table** @pages, align 8
  %40 = load i32, i32* %1, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds %struct.page_table, %struct.page_table* %39, i64 %41
  %43 = getelementptr inbounds %struct.page_table, %struct.page_table* %42, i32 0, i32 1
  %44 = getelementptr inbounds [0 x %struct.page_child], [0 x %struct.page_child]* %43, i64 0, i64 0
  %45 = bitcast %struct.page_child* %44 to i8*
  %46 = bitcast %struct.page_child* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %45, i8* align 8 %46, i64 16, i1 false)
  %47 = load %struct.page_table*, %struct.page_table** @pages, align 8
  %48 = load i32, i32* %1, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds %struct.page_table, %struct.page_table* %47, i64 %49
  %51 = bitcast %struct.page_table* %50 to i16*
  %52 = load i16, i16* %51, align 8
  %53 = and i16 %52, -16
  %54 = or i16 %53, 3
  store i16 %54, i16* %51, align 8
  %55 = load %struct.page_table*, %struct.page_table** @pages, align 8
  %56 = load i32, i32* %1, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds %struct.page_table, %struct.page_table* %55, i64 %57
  %59 = bitcast %struct.page_table* %58 to i16*
  %60 = load i16, i16* %59, align 8
  %61 = and i16 %60, -257
  %62 = or i16 %61, 256
  store i16 %62, i16* %59, align 8
  %63 = load %struct.page_table*, %struct.page_table** @pages, align 8
  %64 = load i32, i32* %1, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds %struct.page_table, %struct.page_table* %63, i64 %65
  %67 = bitcast %struct.page_table* %66 to i16*
  %68 = load i16, i16* %67, align 8
  %69 = and i16 %68, -241
  store i16 %69, i16* %67, align 8
  br label %70

; <label>:70:                                     ; preds = %29
  %71 = load i32, i32* %1, align 4
  %72 = add nsw i32 %71, 1
  store i32 %72, i32* %1, align 4
  br label %26

; <label>:73:                                     ; preds = %26
  %74 = load %struct.pagination_general_configuration*, %struct.pagination_general_configuration** @pag_config, align 8
  %75 = call i32 (i8*, %struct.pagination_general_configuration*, ...) bitcast (i32 (...)* @chiara_asm to i32 (i8*, %struct.pagination_general_configuration*, ...)*)(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), %struct.pagination_general_configuration* %74)
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #1

declare dso_local i32 @chiara_asm(...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @chiara_handle_bad_opcode() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @chiara_handle_no_stack_pointer() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @chiara_handle_bad_permissions() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @chiara_handle_bad_adress() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @init_interrupts() #0 {
  %1 = alloca i32, align 4
  %2 = call i64 @get_next_virtual_adress(i32 4080)
  %3 = inttoptr i64 %2 to %struct.interrupt*
  store %struct.interrupt* %3, %struct.interrupt** @chiara64_interrupt, align 8
  %4 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %5 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %4, i64 0
  %6 = bitcast %struct.interrupt* %5 to i8*
  %7 = load i8, i8* %6, align 8
  %8 = and i8 %7, -2
  %9 = or i8 %8, 1
  store i8 %9, i8* %6, align 8
  %10 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %11 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %10, i64 0
  %12 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %11, i32 0, i32 1
  store i64 ptrtoint (void ()* @chiara_handle_no_stack_pointer to i64), i64* %12, align 8
  %13 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %14 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %13, i64 1
  %15 = bitcast %struct.interrupt* %14 to i8*
  %16 = load i8, i8* %15, align 8
  %17 = and i8 %16, -2
  %18 = or i8 %17, 1
  store i8 %18, i8* %15, align 8
  %19 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %20 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %19, i64 1
  %21 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %20, i32 0, i32 1
  store i64 ptrtoint (void ()* @chiara_handle_bad_permissions to i64), i64* %21, align 8
  %22 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %23 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %22, i64 2
  %24 = bitcast %struct.interrupt* %23 to i8*
  %25 = load i8, i8* %24, align 8
  %26 = and i8 %25, -2
  %27 = or i8 %26, 1
  store i8 %27, i8* %24, align 8
  %28 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %29 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %28, i64 2
  %30 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %29, i32 0, i32 1
  store i64 ptrtoint (void ()* @chiara_handle_bad_opcode to i64), i64* %30, align 8
  %31 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %32 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %31, i64 3
  %33 = bitcast %struct.interrupt* %32 to i8*
  %34 = load i8, i8* %33, align 8
  %35 = and i8 %34, -2
  %36 = or i8 %35, 1
  store i8 %36, i8* %33, align 8
  %37 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %38 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %37, i64 3
  %39 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %38, i32 0, i32 1
  store i64 ptrtoint (void ()* @chiara_handle_bad_adress to i64), i64* %39, align 8
  store i32 4, i32* %1, align 4
  br label %40

; <label>:40:                                     ; preds = %56, %0
  %41 = load i32, i32* %1, align 4
  %42 = icmp slt i32 %41, 255
  br i1 %42, label %43, label %59

; <label>:43:                                     ; preds = %40
  %44 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %45 = load i32, i32* %1, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %44, i64 %46
  %48 = bitcast %struct.interrupt* %47 to i8*
  %49 = load i8, i8* %48, align 8
  %50 = and i8 %49, -2
  store i8 %50, i8* %48, align 8
  %51 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %52 = load i32, i32* %1, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %51, i64 %53
  %55 = getelementptr inbounds %struct.interrupt, %struct.interrupt* %54, i32 0, i32 1
  store i64 0, i64* %55, align 8
  br label %56

; <label>:56:                                     ; preds = %43
  %57 = load i32, i32* %1, align 4
  %58 = add nsw i32 %57, 1
  store i32 %58, i32* %1, align 4
  br label %40

; <label>:59:                                     ; preds = %40
  %60 = load %struct.interrupt*, %struct.interrupt** @chiara64_interrupt, align 8
  %61 = call i32 (i8*, %struct.interrupt*, ...) bitcast (i32 (...)* @chiara_asm to i32 (i8*, %struct.interrupt*, ...)*)(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0), %struct.interrupt* %60)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @init_restraint_mode() #0 {
  %1 = call i32 (i8*, ...) bitcast (i32 (...)* @chiara_asm to i32 (i8*, ...)*)(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.2, i32 0, i32 0))
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  call void @init_pagination()
  call void @init_interrupts()
  call void @init_restraint_mode()
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 7.0.1-8+deb10u2 (tags/RELEASE_701/final)"}
