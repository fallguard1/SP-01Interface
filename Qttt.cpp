#include <QtWidgets\QApplication>
#include <QtWidgets\QMainWindow>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QWidget>

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Qt Interface Example");
        resize(400, 200);

        // Главный виджет и layout
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        // Первый выбор (2 пункта)
        firstChoiceCombo = new QComboBox();
        firstChoiceCombo->addItem("Option 1");
        firstChoiceCombo->addItem("Option 2");
        layout->addWidget(firstChoiceCombo);

        // Второй выбор (10 пунктов, зависит от первого)
        secondChoiceCombo = new QComboBox();
        layout->addWidget(secondChoiceCombo);

        // Поле для ввода
        inputField = new QLineEdit();
        inputField->setPlaceholderText("Enter some text...");
        layout->addWidget(inputField);

        // Кнопка сохранения
        saveButton = new QPushButton("Save");
        layout->addWidget(saveButton);

        setCentralWidget(centralWidget);

        // Обновляем второй ComboBox при изменении первого (новый синтаксис Qt 5+)
        connect(firstChoiceCombo, &QComboBox::currentIndexChanged,
            this, [this](int index) { updateSecondComboBox(index); });

        // Обработка нажатия кнопки (новый синтаксис)
        connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveSelections);

        // Инициализируем второй ComboBox
        updateSecondComboBox(0);
    }

private:
    QComboBox* firstChoiceCombo;
    QComboBox* secondChoiceCombo;
    QLineEdit* inputField;
    QPushButton* saveButton;

    void updateSecondComboBox(int index) {
        secondChoiceCombo->clear();
        if (index == 0) { // Option 1
            for (int i = 1; i <= 10; ++i) {
                secondChoiceCombo->addItem(QString("Sub-option %1 (from Option 1)").arg(i));
            }
        }
        else { // Option 2
            for (int i = 1; i <= 10; ++i) {
                secondChoiceCombo->addItem(QString("Sub-option %1 (from Option 2)").arg(i));
            }
        }
    }

    void saveSelections() {
        if (inputField->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Input field cannot be empty!");
            return;
        }

        QString firstChoice = firstChoiceCombo->currentText();
        QString secondChoice = secondChoiceCombo->currentText();
        QString userInput = inputField->text();

        QMessageBox::information(this, "Success",
            QString("Saved:\nFirst choice: %1\nSecond choice: %2\nInput: %3")
            .arg(firstChoice, secondChoice, userInput));
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}


/*
#include <QtWidgets\QApplication>
#include <QtWidgets\QWidget>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QLabel>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Выбор и ввод данных");

    QVBoxLayout* layout = new QVBoxLayout(&window);

    // Создаем выпадающий список с не изменяемыми элементами
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("Выбор 1");
    comboBox->addItem("Выбор 2");
    comboBox->setEditable(false); // Делаем выбор не изменяемым
    layout->addWidget(comboBox);

    // Поля для ввода
    QLineEdit* inputFields[5];
    QLabel* labels[5];

    // Инициализируем поля и метки
    for (int i = 0; i < 5; ++i) {
        labels[i] = new QLabel();
        inputFields[i] = new QLineEdit();
        layout->addWidget(labels[i]);
        layout->addWidget(inputFields[i]);
        labels[i]->hide(); // Скрываем изначально
        inputFields[i]->hide(); // Скрываем изначально
    }

    QPushButton* submitButton = new QPushButton("Отправить");
    layout->addWidget(submitButton);

    QObject::connect(comboBox, &QComboBox::currentIndexChanged, [&](int index) {
        // Скрываем все поля и метки
        for (int i = 0; i < 5; ++i) {
            labels[i]->hide();
            inputFields[i]->hide();
        }

        // Показываем поля в зависимости от выбора
        if (index == 0) { // Выбор 1
            labels[0]->setText("Поле ввода 1 для выбора 1:");
            labels[1]->setText("Поле ввода 2 для выбора 1:");
            labels[2]->setText("Поле ввода 3 для выбора 1:");
            labels[3]->setText("Поле ввода 4 для выбора 1:");
            labels[4]->setText("Поле ввода 5 для выбора 1:");

            for (int i = 0; i < 5; ++i) {
                labels[i]->show();
                inputFields[i]->show();
            }
        }
        else if (index == 1) { // Выбор 2
            labels[0]->setText("Поле ввода 1 для выбора 2:");
            labels[1]->setText("Поле ввода 2 для выбора 2:");
            labels[2]->setText("Поле ввода 3 для выбора 2:");
            labels[3]->setText("Поле ввода 4 для выбора 2:");
            labels[4]->setText("Поле ввода 5 для выбора 2:");

            for (int i = 0; i < 5; ++i) {
                labels[i]->show();
                inputFields[i]->show();
            }
        }
        });

    QObject::connect(submitButton, &QPushButton::clicked, [&]() {
        QStringList data;
        for (int i = 0; i < 5; ++i) {
            if (inputFields[i]->isVisible() && inputFields[i]->text().isEmpty()) {
                QMessageBox::warning(&window, QString::fromLocal8Bit("Ошибка"), QString::fromLocal8Bit("Заполните все поля!"));
                return;
            }
            if (inputFields[i]->isVisible()) {
                data << inputFields[i]->text();
            }
        }

        // Здесь вы можете использовать переменные data
        QMessageBox::information(&window, QString::fromLocal8Bit("Данные"), QString::fromLocal8Bit("Данные отправлены:\n") + data.join("\n"));
        });

    window.show();
    return app.exec();
}
*/


/*
#include <QtWidgets\QApplication>
#include <QtWidgets\QWidget>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QTextEdit>
#include <QtCore\QString>


class MyWindow : public QWidget {
public:
    MyWindow(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        // Поле для ввода
        inputField = new QLineEdit(this);
        layout->addWidget(inputField);

        // Кнопка
        QPushButton* button = new QPushButton(QString::fromLocal8Bit("Отправить"), this);
        layout->addWidget(button);

        // Поле для вывода
        outputField = new QTextEdit(this);
        outputField->setReadOnly(true);
        layout->addWidget(outputField);

        // Подключаем кнопку к лямбда-функции
        connect(button, &QPushButton::clicked, [this]() {
            QString inputText = inputField->text();
            if (!inputText.isEmpty()) {
                // Сохраняем данные в переменную
                storedData = inputText;

                // Выводим данные в текстовое поле
                outputField->append(storedData);
                inputField->clear(); // Очищаем поле ввода после отправки
            }
            });
    }

private:
    QLineEdit* inputField;
    QTextEdit* outputField;
    QString storedData;
};

int main(int argc, char* argv[]) {
    
    QApplication app(argc, argv);

    MyWindow window;
    window.setWindowTitle(QString::fromLocal8Bit("Программа"));
    window.resize(400, 300);
    window.show();

    return app.exec();
}
*/
/*
#include <QtWidgets\QApplication>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QMessageBox>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Создаем кнопку
    QPushButton button("Press me!");

    // Подключаем сигнал нажатия кнопки к слоту, который показывает сообщение
    QObject::connect(&button, &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Message", "Button is pressed!");
        });

    // Устанавливаем размер и показываем кнопку
    button.resize(200, 100);
    button.show();

    return app.exec();
}
*/