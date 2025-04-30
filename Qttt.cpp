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