#include "E-mail.h"
#include "Functions.h"



void send_email() {
    cout << "Enter your email:" << endl;
    char adr[100]; 
    cin >> adr;
    while (!isCorrectEmail(adr)) {
        cout << "Wrong format. Try again:" << endl;
        cin >> adr;
    }

    cout << "Enter text of email:" << endl;
    char body[1000];
    cin.getline(body, 1000);
    cin.getline(body, 1000);

    //Объект mailman используется для отправки и получения электронной почты
    CkMailMan mailman;

    //Установка SMTP-сервера
    mailman.put_SmtpHost("smtp.mail.ru");

    mailman.put_SmtpSsl(true);
    mailman.put_SmtpPort(465);

    //Установите логин/пароль SMTP (если требуется)
    mailman.put_SmtpUsername("mariya.ignateva.01@mail.ru");
    mailman.put_SmtpPassword("10197sas");

    //Создание нового объекта электронной почты
    CkEmail email;

    email.put_Subject("E-mail");
    email.put_Body(body);
    email.put_From("Maria <mariya.ignateva.01@mail.ru>");
    bool success = email.AddTo("Tester", adr);
    //Чтобы добавить больше получателей, вызовите AddTo, AddCC или AddBcc один раз для каждого получателя.

    // Вызовите Send Email для подключения к SMTP-серверу и отправки.
    // Соединение (т.е. сеанс) с SMTP-сервером остается откройте его, чтобы последующие вызовы SendEmail могли использовать то же самое соединение.
  
    success = mailman.SendEmail(email);
    if (success != true) {
        std::cout << mailman.lastErrorText() << "\r\n";
        cout << "Error: mail was not sent!" << "\r\n";
        return;
    }

    //Некоторые SMTP - серверы фактически не отправляют электронную почту до тех пор, пока соединение не будет закрыто.
    //В этих случаях необходимо вызвать CloseSmtpConnection для отправки почты.
    //Большинство SMTP - серверов отправляют электронное письмо немедленно, и нет необходимости закрывать соединение. Мы закроем ее для примера :
    success = mailman.CloseSmtpConnection();
    if (success != true) {
        std::cout << "Connection to SMTP server not closed cleanly." << "\r\n";
    }

    cout << "Mail Sent!" << "\r\n";
}