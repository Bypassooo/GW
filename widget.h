#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QDir>
#include <QTextCodec>
#include <QByteArray>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void EncryPassWord();
    void DecryPassWord();
    QString byteToQString(const QByteArray &byte);
    QByteArray qstringToByte(const QString &strInfo);
    QString XorEncryptDecrypt(const QString &, const char &);
    bool IfAlarm();
private slots:
    void timeupdate();
    void connectgwdatabase();
    void query_xh_orderamtandqty();
    void query_qh_orderamtandqty();
    void query_qq_orderamtandqty();
    void query_xh_orderspeedmax();
    void query_qh_orderspeedmax();
    void query_qq_orderspeedmax();
    void query_xh_matchamtandqty();
    void query_qh_matchamtandqty();
    void query_qq_matchamtandqty();
    void query_xh_matchspeedmax();
    void query_qh_matchspeedmax();
    void query_qq_matchspeedmax();
    void query_xh_azps();
    void query_xh_hssscj();
    void query_xh_cdqr();
    void query_xh_xhwtqr();
    void query_xh_xhwtwb();
    void query_xh_sccd();
    void query_xh_qhwtwb();
    void query_xh_qhwtfs();
    void query_xh_qhwtsb();

private:
    Ui::Widget *ui;
    QTimer *m_pTimer_xh_orderamtandqty;
    QTimer *m_pTimer_qh_orderamtandqty;
    QTimer *m_pTimer_qq_orderamtandqty;
    QTimer *m_pTimer_xh_orderspeedmax;
    QTimer *m_pTimer_qh_orderspeedmax;
    QTimer *m_pTimer_qq_orderspeedmax;
    QTimer *m_pTimer_xh_matchamtandqty;
    QTimer *m_pTimer_qh_matchamtandqty;
    QTimer *m_pTimer_qq_matchamtandqty;
    QTimer *m_pTimer_xh_matchspeedmax;
    QTimer *m_pTimer_qh_matchspeedmax;
    QTimer *m_pTimer_qq_matchspeedmax;
    QTimer *m_pTimer_xh_azps;
    QTimer *m_pTimer_xh_hssscj;
    QTimer *m_pTimer_xh_cdqr;
    QTimer *m_pTimer_xh_xhwtqr;
    QTimer *m_pTimer_xh_xhwtwb;
    QTimer *m_pTimer_xh_sccd;
    QTimer *m_pTimer_xh_qhwtwb;
    QTimer *m_pTimer_xh_qhwtfs;
    QTimer *m_pTimer_xh_qhwtsb;
public:
    QSqlDatabase gwdb;
    static int refresh[9];  //刷新频率
    static int alertcount;  //警报响的次数
    static QString iniPath;
    static QString VidioPath;
    static QString PicPath;
    static QString ip;
    static QString instance;
    static QString user;
    static QString password;
    static QString Currentpath;
    static int passwordflag;
    static QString morningbegin;
    static QString morningend;
    static QString afterbegin;
    static QString afterend;
    //告警持续3分钟后停止
   // int closealert[9]={0,0,0,0,0,0,0,0,0};
};

#endif // WIDGET_H
