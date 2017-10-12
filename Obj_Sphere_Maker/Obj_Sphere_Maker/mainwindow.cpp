#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file_dir = "/Users/gordiig/Desktop/Obj_Sphere_Maker/new.obj";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_Button_clicked()
{
    out_file.open(file_dir.toStdString());
    double radius = ui->Radius_SpinBox->value();
    int n = ui->n_SpinBox->value();
    int m = ui->m_SpinBox->value();

    if ((m % 2) == 1)
    {
        ui->Err_Label->setText("Ошибка!\nНеверно указано количество высот!");
        out_file.close();
        return;
    }

    vWriter(n, m, radius);
    vtWriter(n, m);

    out_file.close();
    ui->Err_Label->setText("Создание файла прошло успешно!");
}


void MainWindow::vWriter(const int n, const int m, const double r)
{
    double alpha = (double)360/(double)n * M_PI/(double)180;
    double beta = (double)180/(double)m * M_PI/(double)180;
    double x = 0;
    double y = 0;
    double z = 0;
    int count = 0;

    // Экватор
    for (int i = 0; i < n; i++)
    {
        x = roundToN(r * cos(alpha*i));
        z = roundToN(r * sin(alpha*i));
        count++;
        out_file << "v " << x << " " << y << " " << z << "\n";
    }

    // Широты/долготы
    for (int i = 1; i <= (m/2)-1; i++)
    {
        x = r * cos(i*beta); // Это же и новый радиус
        y = r * sin(i*beta);

        std::vector<Dot> dots;
        for (int j = 0; j < n; j++)
        {
            Dot circle;
            circle.x = roundToN(x * cos(alpha*j));
            circle.y = roundToN(y);
            circle.z = roundToN(x * sin(alpha*j));
            count += 2;
            out_file << "v " << circle.x << " " << circle.y << " "
                     << circle.z << "\n";
            dots.push_back(circle);
        }
        for (int j = 0; j < dots.size(); j++)
        {
            out_file << "v " << dots[j].x << " " << -dots[j].y << " "
                     << dots[j].z << "\n";
        }
    }

    // Полюса
    x = 0;
    y = r;
    z = 0;
    count += 2;
    out_file << "v " << x << " " << y << " " << z << " \n";
    out_file << "v " << x << " " << -y << " " << z << " \n";

    out_file << "# " << count << " dots \n";
}

void MainWindow::vtWriter(const int n, const int m)
{
    out_file << "\no Sphere \n";
    int dots_num = n + 2 + (m-2)*n; // Экватор + 2 полюса + остальное
    int poly_cnt = 0;

    // Связанные с экватором
    for (int i = 0; i < n; i++)
    {
        int j = (i == n-1) ? (0) : (i+1);
        out_file << "f " << n+i+1 << " " << n+j+1 << " "
                 << j+1 << " " << i+1 << "\n";
        out_file << "f " << i+1 << " " << j+1 << " "
                 << n+n+j+1 << " " << n+n+i+1 << "\n";
        poly_cnt += 2;
    }

    // Остальные
    int schet = 1;
    int i_for_ost = 1;
    while (schet <= m/2 - 2)
    {
        for (int j = 0; j < n; j++)
        {
            int k = (j == n-1) ? (0) : (j+1);

            out_file << "f " << n*(i_for_ost+2)+j+1 << " " << n*(i_for_ost+2)+k+1 << " "
                     << n*i_for_ost+k+1 << " " << n*i_for_ost+j+1 << "\n";
            out_file << "f " << n*(i_for_ost+1)+j+1 << " " << n*(i_for_ost+1)+k+1 << " "
                     << n*(i_for_ost+3)+k+1 << " " << n*(i_for_ost+3)+j+1 << "\n";
            poly_cnt += 2;
        }
        schet++;
        i_for_ost += 2;
    }

    // Полюсные
    for (int i = 0; i < n; i++)
    {
        int j = (i == n-1) ? (0) : (i+1);

        out_file << "f " << dots_num - 2-n+i + 1 << " " << dots_num - 2-n+j + 1 << " "
                 << dots_num << "\n";
        out_file << "f " << dots_num - 2-2*n+j + 1 << " " << dots_num - 2-2*n+i + 1 << " "
                 << dots_num-1 << "\n";
        poly_cnt += 2;
    }

    out_file << "# " << poly_cnt << " polygons\n";
}

void MainWindow::on_Dir_Button_clicked()
{
    file_dir = QFileDialog::getExistingDirectory(0, "Сохранить в:");
    file_dir += "/new.obj";
}

double MainWindow::roundToN(double num, int n)
{
    double ans = fabs(num);
    double sign = (num >= 0) ? (1) : (-1);

    ans = round(ans * 10*n);
    if (ans == 0)
    {
        return 0;
    }

    ans = (double)ans / (double)(10.*n);
    return sign*ans;
}
