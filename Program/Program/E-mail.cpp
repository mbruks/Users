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

    //������ mailman ������������ ��� �������� � ��������� ����������� �����
    CkMailMan mailman;

    //��������� SMTP-�������
    mailman.put_SmtpHost("smtp.mail.ru");

    mailman.put_SmtpSsl(true);
    mailman.put_SmtpPort(465);

    //���������� �����/������ SMTP (���� ���������)
    mailman.put_SmtpUsername("mariya.ignateva.01@mail.ru");
    mailman.put_SmtpPassword("10197sas");

    //�������� ������ ������� ����������� �����
    CkEmail email;

    email.put_Subject("E-mail");
    email.put_Body(body);
    email.put_From("Maria <mariya.ignateva.01@mail.ru>");
    bool success = email.AddTo("Tester", adr);
    //����� �������� ������ �����������, �������� AddTo, AddCC ��� AddBcc ���� ��� ��� ������� ����������.

    // �������� Send Email ��� ����������� � SMTP-������� � ��������.
    // ���������� (�.�. �����) � SMTP-�������� �������� �������� ���, ����� ����������� ������ SendEmail ����� ������������ �� �� ����� ����������.
  
    success = mailman.SendEmail(email);
    if (success != true) {
        std::cout << mailman.lastErrorText() << "\r\n";
        cout << "Error: mail was not sent!" << "\r\n";
        return;
    }

    //��������� SMTP - ������� ���������� �� ���������� ����������� ����� �� ��� ���, ���� ���������� �� ����� �������.
    //� ���� ������� ���������� ������� CloseSmtpConnection ��� �������� �����.
    //����������� SMTP - �������� ���������� ����������� ������ ����������, � ��� ������������� ��������� ����������. �� ������� �� ��� ������� :
    success = mailman.CloseSmtpConnection();
    if (success != true) {
        std::cout << "Connection to SMTP server not closed cleanly." << "\r\n";
    }

    cout << "Mail Sent!" << "\r\n";
}