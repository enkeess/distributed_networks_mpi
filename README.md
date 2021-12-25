## Задание по курсу "Распределенные системы"

1. В транспьютерной матрице размером 5*5, в каждом узле которой находится один процесс, необходимо выполнить операцию сбора данных (длиной 4 байта) от всех процессов для одного (MPI_GATHER) - процесса с координатами (0,0).
    
    Реализовать программу, моделирующую выполнение операции MPI_GATHER на транспьютерной матрице 
    при помощи пересылок MPI типа точка-точка.
    
    Оценить сколько времени потребуется для выполнения операции MPI_GATHER, 
    если все процессы выдали эту операцию редукции одновременно. 
    Время старта равно 100, время передачи байта равно 1 (Ts=100,Tb=1). 
    Процессорные операции, включая чтение из памяти и запись в память, 
    считаются бесконечно быстрыми.
    
2. Доработать MPI-программу, реализованную в рамках курса “Суперкомпьютеры и параллельная обработка данных”. 
    Добавить контрольные точки для продолжения работы программы в случае сбоя. 
    Реализовать один из 3-х сценариев работы после сбоя: 
    * продолжить работу программы только на “исправных” процессах; 
    * вместо процессов, вышедших из строя, создать новые MPI-процессы, 
    которые необходимо использовать для продолжения расчетов; 
    * при запуске программы на счет сразу запустить некоторое дополнительное количество MPI-процессов, 
    которые использовать в случае сбоя.


## 1) Первое задание 

### Как скомпилировать

```
cd task1
make
```

### Как запустить

```
    mpirun -n 25 --oversubscribe ./task1.out
```


## 2) Второе задание - для запуска необходимо установить Docker
### Как скомпилировать

```
cd task2
docker pull abouteiller/mpi-ft-ulfm
source dockervars.sh    
make
```

### Как запустить

```
    mpirun -np 32 --with-ft ulfm ./task2 26
```



