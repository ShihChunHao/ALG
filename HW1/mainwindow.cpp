#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//swap_function
void swap(int &a,int &b){
    int t;
    t=a;
    a=b;
    b=t;
}

//HeapSort_func2
void MHeapify(QVector<int> &array, int root, int length){

    int left = 2*root,      // 取得left child
    right = 2*root + 1,     // 取得right child
    largest;                // largest用來記錄包含root與child, 三者之中Key最大的node

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root) {
        swap(array[largest], array[root]);
        MHeapify(array, largest, length);        // 調整新的subtree成Max Heap
    }
}
//HeapSort_func1
void BuildMaxHeap(QVector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        MHeapify(array, i, (int)array.size() - 1);     // length要減一, 因為heap從1開始存放資料
    }
}
//堆積排序
void heap_sort(QVector<int> &array){
    array.insert(array.begin(), 0);                     // 將index(0)閒置

    BuildMaxHeap(array);                                // 將array調整成Max Heap

    int size = (int)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (int i = (int)array.size() -1; i >= 2; i--) {
        swap(array[1], array[i]);                       // 將最大值放到array的最後一個位置
        size--;
        MHeapify(array, 1, size);                     // 調整「忽略最後一個位置」的矩陣
    }

    array.erase(array.begin());                         // 將index(0)刪除
}

//binary
int binarysearch(QVector<int> &data, int search, int n)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (data[mid] == search)
        {
            return mid;
        }
        else if (data[mid] > search)
        {
            high = mid - 1;
        }
        else if (data[mid] < search)
        {
            low = mid + 1;
        }
    }
    return -1;
}

//Verify_is_digit
bool VerifyNumber(QString str)
{
    //切割字串比較是否為數字
    std::string temp = str.toStdString();
    for (int i = 0; i < str.length(); i++)
    {
        if (temp[i]<'0' || temp[i]>'9')
        {
            return false;
        }
    }
    return true;
}

//QuickSort
void QuickSort(QVector<int> &arr, int left, int right)
{
    if(left < right) {
            int s = arr[(left+right)/2];
            int i = left - 1;
            int j = right + 1;

            while(1) {
                while(arr[++i] < s) ;  // 向右找
                while(arr[--j] > s) ;  // 向左找
                if(i >= j)
                    break;
                swap(arr[i], arr[j]);
            }

            QuickSort(arr, left, i-1);   // 對左邊進行遞迴
            QuickSort(arr, j+1, right);  // 對右邊進行遞迴
        }
}

//selection_sort
void selection_sort(QVector<int> &arr){
    for(int i=0;i<arr.length();i++){
        for(int j=i+1;j<arr.length();j++){
            if(arr[i]>arr[j]){
                swap(arr[i],arr[j]);
            }
        }
    }
}

//bubble_sort
void bubble_sort(QVector<int> &arr){
    for (int i=0; i<arr.length()-1; i++) {
        for (int j=0; j<arr.length()-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

//insertion
void insertion_sort(QVector<int> &arr){
    for (int i = 0; i < arr.length() - 1; i++) {
        int j = i + 1;
        int tmp = arr[j];
        while (j > 0 && tmp > arr[j - 1]) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = tmp;
    }
}

//Randon_Generate
void MainWindow::on_pushButton_clicked()
{
    if(ui->number->text().length() == 0){
        QMessageBox::about(this, "警告！","請輸入想要產生的數字個輸入到n之中！");
    }
    if(ui->range->text().length() == 0){
        QMessageBox::about(this, "警告！","請輸入想要產生的數字的範圍輸入到range之中！");
    }
    if(VerifyNumber(ui->number->text())==0 || VerifyNumber(ui->range->text())==0){
        QMessageBox::about(this, "警告！","你輸入到不是數字！");
        if(VerifyNumber(ui->number->text())==0){
            ui->number->clear();
        }
        if(VerifyNumber(ui->range->text())==0){
            ui->range->clear();
        }
    }else{
        ui->result->clear();
        int n=ui->number->text().toInt();
        int range=ui->range->text().toInt();

        srand(time(NULL));
        for(int i=0;i<n;i++){
            int x=arc4random()%range;
            v.push_back(x);
            ui->result->append("data["+QString::number(i)+"] = "+QString::number(x));
        }
        ui->result->append("亂數生成完畢！");
    }
}
//selection_button
void MainWindow::on_pushButton_2_clicked()
{
    ui->result_2->clear();
    QVector<int> v2(v);
    // 儲存時間用的變數
    clock_t startTime,endTime;
    startTime = clock();

    // 主要計算
    selection_sort(v2);

    // 計算結束時間
    endTime = clock();

    // 計算實際花費時間
    double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    if(dnp%2 == 0){
        //print
        for(int i=0;i<v2.length();i++){
            ui->result_2->append("data["+QString::number(i)+"] = "+QString::number(v2[i]));
        }
    }
    else{
        ui->result_2->append("排序完成！");
    }
    //sortcheck
    if(sort_check%2 != 0){
        qDebug() << "hi"<<Qt::endl;
        QVector<int> v3(v);
        QuickSort(v3, 0, v3.length() - 1);
        if(v2==v3){
            qDebug() << "hi1"<<Qt::endl;
            ui->result_2->append("Sorted! Correct!");
        }
        else{
            qDebug() << "hi2"<<Qt::endl;
            ui->result_2->append("Sorted! Wrong!");
        }
    }
    ui->result_2->append("Time: "+QString::number(time_used)+" sec");

    v2.clear();
}
//bubble_button
void MainWindow::on_pushButton_3_clicked()
{
    ui->result_3->clear();
    QVector<int> v2(v);
    // 儲存時間用的變數
    clock_t startTime,endTime;
    startTime = clock();
    // 主要計算
    bubble_sort(v2);
    // 計算結束時間
    endTime = clock();

    // 計算實際花費時間
    double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

    if(dnp%2 == 0){
        //print
        for(int i=0;i<v2.length();i++){
            ui->result_3->append("data["+QString::number(i)+"] = "+QString::number(v2[i]));
        }
    }
    else{
        ui->result_3->append("排序完成！");
    }
    //sortcheck
    if(sort_check%2 != 0){
        QVector<int> v3(v);
        QuickSort(v3, 0, v3.length() - 1);
        if(v2==v3){
            ui->result_3->append("Sorted! Correct!");//: "+QString::number(time_used)+" sec");
        }
        else{
            ui->result_3->append("Sorted! Wrong!");
        }
    }
    ui->result_3->append("Time: "+QString::number(time_used)+" sec");
    v2.clear();
}
//Quick_button
void MainWindow::on_pushButton_4_clicked()
{
    ui->result_4->clear();
    QVector<int> v2(v);

    clock_t startTime,endTime;
    startTime = clock();
    QuickSort(v2, 0, v2.length() - 1);
    // 計算結束時間
    endTime = clock();

    // 計算實際花費時間
    double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

    if(dnp%2 == 0){
        //print
        for(int i=0;i<v2.length();i++){
            ui->result_4->append("data["+QString::number(i)+"] = "+QString::number(v2[i]));
        }
    }
    else{
        ui->result_4->append("排序完成！");
    }
    //sortcheck
    if(sort_check%2 != 0){
        QVector<int> v3(v);
        QuickSort(v3, 0, v3.length() - 1);
        if(v2==v3){
            ui->result_4->append("Sorted! Correct!");//: "+QString::number(time_used)+" sec");
        }
        else{
            ui->result_4->append("Sorted! Wrong!");
        }
    }
    ui->result_4->append("Time: "+QString::number(time_used)+" sec");
    v2.clear();
}
//insertion_button
void MainWindow::on_pushButton_5_clicked()
{
    ui->result_5->clear();
    QVector<int> v2(v);
    clock_t startTime,endTime;
    startTime = clock();

    insertion_sort(v2);

    // 計算結束時間
    endTime = clock();
    // 計算實際花費時間
    double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

    if(dnp%2 == 0){
        //print
        int j = 0;
        for(int i=v2.length()-1;i>=0;i--){
            ui->result_5->append("data["+QString::number(j)+"] = "+QString::number(v2[i]));
            j++;
        }
    }
    else{
        ui->result_5->append("排序完成！");
    }
    //sortcheck
    if(sort_check%2 != 0){
        QVector<int> v3(v);
        insertion_sort(v3);;
        if(v2==v3){
            ui->result_5->append("Sorted! Correct!");//: "+QString::number(time_used)+" sec");
        }
        else{
            ui->result_5->append("Sorted! Wrong!");
        }
    }
    ui->result_5->append("Time: "+QString::number(time_used)+" sec");

    v2.clear();
}
//堆積排序
void MainWindow::on_pushButton_9_clicked()
{
    ui->result_7->clear();
    QVector<int> v2(v);
    clock_t startTime,endTime;
    startTime = clock();
//    insertion_sort(v2);
    heap_sort(v2);
    // 計算結束時間
    endTime = clock();
    // 計算實際花費時間
    double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

    if(dnp%2 == 0){
        //print
        for(int i=0;i<v2.length();i++){
            ui->result_7->append("data["+QString::number(i)+"] = "+QString::number(v2[i]));
        }
    }
    else{
        ui->result_7->append("排序完成！");
    }
    //sortcheck
    if(sort_check%2 != 0){
        QVector<int> v3(v);
        QuickSort(v3, 0, v3.length() - 1);
        if(v2==v3){
            ui->result_7->append("Sorted! Correct!");//: "+QString::number(time_used)+" sec");
        }
        else{
            ui->result_7->append("Sorted! Wrong!");
        }
    }
    ui->result_7->append("Time: "+QString::number(time_used)+" sec");
    v2.clear();
}
//Binary_button
void MainWindow::on_pushButton_6_clicked()
{
    if(ui->Target->text().length() == 0){
        QMessageBox::about(this, "警告！","請輸入想要找的數字輸入到欄位之中！");
    }
    while(VerifyNumber(ui->Target->text())==0){
        QMessageBox::about(this, "警告！","你輸入到不是數字！");
        ui->Target->clear();
    }
    int tar = ui->Target->text().toInt();
    ui->result_6->clear();
    QVector<int> v2(v);
    QuickSort(v2, 0, v2.length() - 1);
    int ans = binarysearch(v2, tar, v2.length());
    if(ans==-1){
        ui->result_6->append("Sorry!! Number is not in list.");
    }else{
        ui->result_6->append("Find!! First "+QString::number(tar)+" is in index: "+QString::number(ans));
    }
}

//圖表（還有細節要修）
/*
void MainWindow::on_pushButton_7_clicked()
{
    QVector<int> v2;
    QLineSeries* line1 = new QLineSeries();
    QLineSeries* line2 = new QLineSeries();
    QLineSeries* line3 = new QLineSeries();
    QLineSeries* line4 = new QLineSeries();
    int n = ui->number->text().toInt();
    int range = ui->range->text().toInt();
    int x = n/5;
    for(int i = 0; i<=n; i+=x)
    {
        srand(time(NULL));
        for(int j=0;j<i;j++){
            int t=arc4random()%range;
            v2.push_back(t);
        }
        QVector<int> v3(v2);
        clock_t startTime,endTime;
        startTime = clock();
        selection_sort(v2);
        endTime = clock();
        double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
        line1->append(i,time_used);
        v2.clear();
        //bbs
        QVector<int> v4(v3);
        startTime = clock();
        bubble_sort(v3);
        endTime = clock();
        time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
        line2->append(i,time_used);
        v3.clear();
        //ins
        QVector<int> v5(v4);
        startTime = clock();
        insertion_sort(v4);
        endTime = clock();
        time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
        line3->append(i,time_used);
        v4.clear();
        //qks
        startTime = clock();
        QuickSort(v5,0,v5.length()-1);
        endTime = clock();
        time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
        line4->append(i,time_used);
        v5.clear();
    }

    QChart* c = new QChart();
    c->addSeries(line1);
    c->addSeries(line2);
    c->addSeries(line3);
    c->addSeries(line4);
    ui->widget->setChart(c);
}
*/

//SortCheck是否勾起
void MainWindow::on_checkBox_clicked()
{
    sort_check += 1;
}

//清除
void MainWindow::on_pushButton_8_clicked()
{
    ui->number->clear();
    ui->range->clear();
    ui->result->clear();
    ui->result_2->clear();
    ui->result_3->clear();
    ui->result_4->clear();
    ui->result_5->clear();
    ui->result_6->clear();
    ui->result_7->clear();
    ui->Target->clear();
    v.clear();
}

//圖表
void MainWindow::on_pushButton_7_clicked(){
     QLineSeries *series = new QLineSeries();
     QLineSeries *series_2 = new QLineSeries();
     QLineSeries *series_3 = new QLineSeries();
     QLineSeries *series_4 = new QLineSeries();
     QLineSeries *series_5 = new QLineSeries();
     QVector<int> v2;

     int n = ui->number->text().toInt();
     int range = ui->range->text().toInt();
     int x = n/5;

     for(int i = 0; i<=n; i+=x)
     {
         srand(time(NULL));
         for(int j=0;j<i;j++){
             int t=arc4random()%range;
             v2.push_back(t);
         }
         QVector<int> v3(v2);
         clock_t startTime,endTime;
         startTime = clock();
         selection_sort(v2);
         endTime = clock();
         double time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
         series->append(i,time_used);
//         line1->append(i,time_used);
         v2.clear();
         //bbs
         QVector<int> v4(v3);
         startTime = clock();
         bubble_sort(v3);
         endTime = clock();
         time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
         series_2->append(i,time_used);
//         line2->append(i,time_used);
         v3.clear();
         //ins
         QVector<int> v5(v4);
         startTime = clock();
         insertion_sort(v4);
         endTime = clock();
         time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
         series_3->append(i,time_used);
//         line3->append(i,time_used);
         v4.clear();
         //qks
         QVector<int> v6(v5);
         startTime = clock();
         QuickSort(v5,0,v5.length()-1);
         endTime = clock();
         time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
         series_4->append(i,time_used);
//         line4->append(i,time_used);
         v5.clear();
         //hs
         startTime = clock();
         heap_sort(v6);
         endTime = clock();
         time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
         series_5->append(i,time_used);
//         line4->append(i,time_used);
         v6.clear();
     }

     QChart *chart = new QChart();
     series->setName(QStringLiteral("selection"));
     series_2->setName(QStringLiteral("bubble"));
     series_3->setName("insertion");
     series_4->setName("quick_sort");
     series_5->setName("heap_sort");
//     chart->legend()->hide();
     chart->addSeries(series);
     chart->addSeries(series_2);
     chart->addSeries(series_3);
     chart->addSeries(series_4);
     chart->addSeries(series_5);
     chart->createDefaultAxes();
     chart->setTitle("Compare of 5 kinds of SORT");
     chart->createDefaultAxes();
     //![4]
     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     //![4]
     //!

     ui->widget->setChart(chart);

}

//Does_not_print sort result
void MainWindow::on_checkBox_2_clicked()
{
    dnp += 1;
}

