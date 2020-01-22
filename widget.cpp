#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSound>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
//#define CLOSEALERT  1

QString Widget::Currentpath = QDir::currentPath();
QString tempint = Widget::Currentpath;
QString tempvio = Widget::Currentpath;
QString temppic = Widget::Currentpath;
QString Widget::iniPath =tempint.append("/config.ini");
QString Widget::VidioPath=tempvio.append("/media/alerm.wav");
QString Widget::PicPath=temppic.append("/pic/logo.png");
QSettings settings_init(Widget::iniPath,QSettings::IniFormat);

int init_a = settings_init.value("/refresh/azps",5).toInt();
int init_b = settings_init.value("/refresh/hssscj",5).toInt();
int init_c = settings_init.value("/refresh/cdqr",5).toInt();
int init_d = settings_init.value("/refresh/xhwtqr",5).toInt();
int init_e = settings_init.value("/refresh/xhwtwb",5).toInt();
int init_f = settings_init.value("/refresh/sccd",5).toInt();
int init_g = settings_init.value("/refresh/qhwtwb",5).toInt();
int init_h = settings_init.value("/refresh/qhwtfs",5).toInt();
int init_i = settings_init.value("/refresh/qhwtsb",5).toInt();

QString Widget::morningbegin = settings_init.value("/monitortime/morningbegin","09:30:00").toString();
QString Widget::morningend   = settings_init.value("/monitortime/morningend","11:30:00").toString();
QString Widget::afterbegin   = settings_init.value("/monitortime/afterbegin","13:00:00").toString();
QString Widget::afterend     = settings_init.value("/monitortime/afterend","15:00:00").toString();
int Widget::alertcount   = settings_init.value("/alermtime/count",10).toInt();

QString fontsize = settings_init.value("/font/size","11px").toString();
QString groupsize = settings_init.value("/font/groupboxsize","20px").toString();
int Widget::refresh[9]={init_a,init_b,init_c,init_d,init_e,init_f,init_g,init_h,init_i};

QString Widget::ip = settings_init.value("/database/ip").toString();
QString Widget::instance = settings_init.value("/database/instance").toString();
QString Widget::user = settings_init.value("/database/user").toString();
QString Widget::password = settings_init.value("/database/password").toString();
int Widget::passwordflag = settings_init.value("/database/changepassword").toInt();
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString logpath = Currentpath;
    logpath.append("/log");
    qDebug()<<logpath;
    QDir dir(logpath);

    if(!dir.exists())
    {
        dir.mkdir(logpath);//只创建一级子目录，即必须保证上级目录存在
    }

    if(passwordflag  == 1)
        EncryPassWord();
    else
        DecryPassWord();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
    timer->start(1000);

    //设置窗口图标
    QIcon icon(PicPath);
    setWindowIcon(icon);
    ui->label_27->setVisible(false);
    ui->label_28->setVisible(false);
    ui->label_29->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);

    QString fontstyle = "font-size:";
    fontstyle.append(fontsize);
    fontstyle.append(";");
    ui->label_1->setStyleSheet(fontstyle);
    ui->label_2->setStyleSheet(fontstyle);
    ui->label_3->setStyleSheet(fontstyle);
    ui->label_4->setStyleSheet(fontstyle);
    ui->label_5->setStyleSheet(fontstyle);
    ui->label_6->setStyleSheet(fontstyle);
    ui->label_7->setStyleSheet(fontstyle);
    ui->label_8->setStyleSheet(fontstyle);
    ui->label_9->setStyleSheet(fontstyle);
    ui->label_10->setStyleSheet(fontstyle);
    ui->label_11->setStyleSheet(fontstyle);
    ui->label_12->setStyleSheet(fontstyle);
    ui->label_13->setStyleSheet(fontstyle);
    ui->label_14->setStyleSheet(fontstyle);
    ui->label_15->setStyleSheet(fontstyle);
    ui->label_16->setStyleSheet(fontstyle);
    ui->label_17->setStyleSheet(fontstyle);
    ui->label_18->setStyleSheet(fontstyle);
    ui->label_19->setStyleSheet(fontstyle);
    ui->label_20->setStyleSheet(fontstyle);
    ui->label_21->setStyleSheet(fontstyle);
    ui->label_22->setStyleSheet(fontstyle);
    ui->label_23->setStyleSheet(fontstyle);
    ui->label_24->setStyleSheet(fontstyle);
    ui->label_25->setStyleSheet(fontstyle);
    ui->label_26->setStyleSheet(fontstyle);
    ui->label_27->setStyleSheet(fontstyle);
    ui->label_28->setStyleSheet(fontstyle);
    ui->label_29->setStyleSheet(fontstyle);
    ui->label_30->setStyleSheet(fontstyle);
    ui->label_31->setStyleSheet(fontstyle);
    ui->label_32->setStyleSheet(fontstyle);
    ui->label_33->setStyleSheet(fontstyle);
    ui->label_34->setStyleSheet(fontstyle);
    ui->label_35->setStyleSheet(fontstyle);
    ui->label_36->setStyleSheet(fontstyle);
    ui->label_37->setStyleSheet(fontstyle);
    ui->label_38->setStyleSheet(fontstyle);
    ui->label_39->setStyleSheet(fontstyle);
    ui->label_40->setStyleSheet(fontstyle);
    ui->label_41->setStyleSheet(fontstyle);
    ui->label_42->setStyleSheet(fontstyle);
    ui->label_43->setStyleSheet(fontstyle);
    ui->label_44->setStyleSheet(fontstyle);
    ui->label_45->setStyleSheet(fontstyle);
    ui->label_46->setStyleSheet(fontstyle);
    ui->label_47->setStyleSheet(fontstyle);

    QString groupstyle = "font-size:";
    groupstyle.append(groupsize);
    groupstyle.append(";");
    ui->groupBox->setStyleSheet(groupstyle);
    ui->groupBox_2->setStyleSheet(groupstyle);
    ui->groupBox_3->setStyleSheet(groupstyle);
    ui->groupBox_4->setStyleSheet(groupstyle);
    ui->groupBox_5->setStyleSheet(groupstyle);

    m_pTimer_xh_orderamtandqty = new QTimer(this);
    m_pTimer_qh_orderamtandqty = new QTimer(this);
    m_pTimer_qq_orderamtandqty = new QTimer(this);
    m_pTimer_xh_orderspeedmax = new QTimer(this);
    m_pTimer_qh_orderspeedmax = new QTimer(this);
    m_pTimer_qq_orderspeedmax = new QTimer(this);
    m_pTimer_xh_matchamtandqty = new QTimer(this);
    m_pTimer_qh_matchamtandqty = new QTimer(this);
    m_pTimer_qq_matchamtandqty = new QTimer(this);
    m_pTimer_xh_matchspeedmax = new QTimer(this);
    m_pTimer_qh_matchspeedmax = new QTimer(this);
    m_pTimer_qq_matchspeedmax = new QTimer(this);
    m_pTimer_xh_azps = new QTimer(this);
    m_pTimer_xh_hssscj = new QTimer(this);
    m_pTimer_xh_cdqr = new QTimer(this);
    m_pTimer_xh_xhwtqr = new QTimer(this);
    m_pTimer_xh_xhwtwb = new QTimer(this);
    m_pTimer_xh_sccd = new QTimer(this);
    m_pTimer_xh_qhwtwb = new QTimer(this);
    m_pTimer_xh_qhwtfs = new QTimer(this);
    m_pTimer_xh_qhwtsb = new QTimer(this);

    connectgwdatabase();
    connect(m_pTimer_xh_orderamtandqty, SIGNAL(timeout()), this, SLOT(query_xh_orderamtandqty()));
    connect(m_pTimer_qh_orderamtandqty, SIGNAL(timeout()), this, SLOT(query_qh_orderamtandqty()));
    connect(m_pTimer_qq_orderamtandqty, SIGNAL(timeout()), this, SLOT(query_qq_orderamtandqty()));
    connect(m_pTimer_xh_orderspeedmax, SIGNAL(timeout()), this, SLOT(query_xh_orderspeedmax()));
    connect(m_pTimer_qh_orderspeedmax, SIGNAL(timeout()), this, SLOT(query_qh_orderspeedmax()));
    connect(m_pTimer_qq_orderspeedmax, SIGNAL(timeout()), this, SLOT(query_qq_orderspeedmax()));
    connect(m_pTimer_xh_matchamtandqty, SIGNAL(timeout()), this, SLOT(query_xh_matchamtandqty()));
    connect(m_pTimer_qh_matchamtandqty, SIGNAL(timeout()), this, SLOT(query_qh_matchamtandqty()));
    connect(m_pTimer_qq_matchamtandqty, SIGNAL(timeout()), this, SLOT(query_qq_matchamtandqty()));
    connect(m_pTimer_xh_matchspeedmax, SIGNAL(timeout()), this, SLOT(query_xh_matchspeedmax()));
    connect(m_pTimer_qh_matchspeedmax, SIGNAL(timeout()), this, SLOT(query_qh_matchspeedmax()));
    connect(m_pTimer_qq_matchspeedmax, SIGNAL(timeout()), this, SLOT(query_qq_matchspeedmax()));
    connect(m_pTimer_xh_azps, SIGNAL(timeout()), this, SLOT(query_xh_azps()));
    connect(m_pTimer_xh_hssscj, SIGNAL(timeout()), this, SLOT(query_xh_hssscj()));
    connect(m_pTimer_xh_cdqr, SIGNAL(timeout()), this, SLOT(query_xh_cdqr()));
    connect(m_pTimer_xh_xhwtqr, SIGNAL(timeout()), this, SLOT(query_xh_xhwtqr()));
    connect(m_pTimer_xh_xhwtwb, SIGNAL(timeout()), this, SLOT(query_xh_xhwtwb()));
    connect(m_pTimer_xh_sccd, SIGNAL(timeout()), this, SLOT(query_xh_sccd()));
    connect(m_pTimer_xh_qhwtwb, SIGNAL(timeout()), this, SLOT(query_xh_qhwtwb()));
    connect(m_pTimer_xh_qhwtfs, SIGNAL(timeout()), this, SLOT(query_xh_qhwtfs()));
    connect(m_pTimer_xh_qhwtsb, SIGNAL(timeout()), this, SLOT(query_xh_qhwtsb()));

    QSettings settings_refresh(iniPath,QSettings::IniFormat);
    int xh_orderamtandqty = settings_refresh.value("/refresh/xh_orderamtandqty",5).toInt();
    int qh_orderamtandqty = settings_refresh.value("/refresh/qh_orderamtandqty",5).toInt();
    int qq_orderamtandqty = settings_refresh.value("/refresh/qq_orderamtandqty",5).toInt();
    int xh_matchamtandqty = settings_refresh.value("/refresh/xh_matchamtandqty",5).toInt();
    int qh_matchamtandqty = settings_refresh.value("/refresh/qh_matchamtandqty",5).toInt();
    int qq_matchamtandqty = settings_refresh.value("/refresh/qq_matchamtandqty",5).toInt();
    int xh_orderspeedmax = settings_refresh.value("/refresh/xh_orderspeedmax",5).toInt();
    int qh_orderspeedmax = settings_refresh.value("/refresh/qh_orderspeedmax",5).toInt();
    int qq_orderspeedmax = settings_refresh.value("/refresh/qq_orderspeedmax",5).toInt();
    int xh_matchspeedmax = settings_refresh.value("/refresh/xh_matchspeedmax",5).toInt();
    int qh_matchspeedmax = settings_refresh.value("/refresh/qh_matchspeedmax",5).toInt();
    int qq_matchspeedmax = settings_refresh.value("/refresh/qq_matchspeedmax",5).toInt();


    m_pTimer_xh_orderamtandqty->start(xh_orderamtandqty*1000);
    m_pTimer_qh_orderamtandqty->start(qh_orderamtandqty*1000);
    m_pTimer_qq_orderamtandqty->start(qq_orderamtandqty*1000);
    m_pTimer_xh_orderspeedmax->start(xh_orderspeedmax*1000);
    m_pTimer_qh_orderspeedmax->start(qh_orderspeedmax*1000);
    m_pTimer_qq_orderspeedmax->start(qq_orderspeedmax*1000);
    m_pTimer_xh_matchamtandqty->start(xh_matchamtandqty*1000);
    m_pTimer_qh_matchamtandqty->start(qh_matchamtandqty*1000);
    m_pTimer_qq_matchamtandqty->start(qq_matchamtandqty*1000);
    m_pTimer_xh_matchspeedmax->start(xh_matchspeedmax*1000);
    m_pTimer_qh_matchspeedmax->start(qh_matchspeedmax*1000);
    m_pTimer_qq_matchspeedmax->start(qq_matchspeedmax*1000);

    m_pTimer_xh_azps->start(refresh[0]*1000);
    m_pTimer_xh_hssscj->start(refresh[1]*1000);
    m_pTimer_xh_cdqr->start(refresh[2]*1000);
    m_pTimer_xh_xhwtqr->start(refresh[3]*1000);
    m_pTimer_xh_xhwtwb->start(refresh[4]*1000);
    m_pTimer_xh_sccd->start(refresh[5]*1000);
    m_pTimer_xh_qhwtwb->start(refresh[6]*1000);
    m_pTimer_xh_qhwtfs->start(refresh[7]*1000);
    m_pTimer_xh_qhwtsb->start(refresh[8]*1000);

}
bool Widget::IfAlarm()
{
    QString appendtime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString appendtimea = appendtime;
    QString appendtimeb = appendtime;
    QString appendtimec = appendtime;
    QString appendtimed = appendtime;
    QString Temp_morningbegin = appendtimea.append(" ").append(morningbegin);
    QString Temp_morningend   = appendtimeb.append(" ").append(morningend);
    QString Temp_afterbegin   = appendtimec.append(" ").append(afterbegin);
    QString Temp_afterend     = appendtimed.append(" ").append(afterend);


    QString Temp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QDateTime TempCurrent = QDateTime::fromString(Temp, "yyyy-MM-dd hh:mm:ss");


    QDateTime Set_morningbegin = QDateTime::fromString(Temp_morningbegin, "yyyy-MM-dd hh:mm:ss");
    QDateTime Set_morningend = QDateTime::fromString(Temp_morningend, "yyyy-MM-dd hh:mm:ss");
    QDateTime Set_afterbegin = QDateTime::fromString(Temp_afterbegin, "yyyy-MM-dd hh:mm:ss");
    QDateTime Set_afterend = QDateTime::fromString(Temp_afterend, "yyyy-MM-dd hh:mm:ss");

    uint a = TempCurrent.toTime_t();
    uint b = Set_morningbegin.toTime_t();
    uint c = Set_morningend.toTime_t();
    uint d = Set_afterbegin.toTime_t();
    uint f = Set_afterend.toTime_t();
    int q = a-b;
    int w = a-c;
    int e = a-d;
    int r = a-f;

    if(( q >= 0 && w <=0 ) || ( e >= 0  && r <= 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString Widget::XorEncryptDecrypt(const QString &str, const char &key)
{
    QString result;
    QByteArray bs = this->qstringToByte(str);
    int i;
    for(i=0; i<bs.size(); i++)
    {
      bs[i] = bs[i] ^ key;
    }
    result = byteToQString(bs);
    return result;
}
QString Widget::byteToQString(const QByteArray &byte)
{
    QString result;
    if(byte.size() > 0)
    {
      QTextCodec *codec = QTextCodec::codecForName("utf-8");
      result = codec->toUnicode(byte);
    }
    return result;
}
QByteArray Widget::qstringToByte(const QString &strInfo)
{
    QByteArray result;
    if(strInfo.length() > 0)
    {
      QTextCodec *codec = QTextCodec::codecForName("utf-8");
      result = codec->fromUnicode(strInfo);
    }
    return result;
}

void Widget::EncryPassWord()
{
    QSettings settings_setpwd(iniPath,QSettings::IniFormat);
    QString pwd = XorEncryptDecrypt(password,12);
    settings_setpwd.setValue("/database/password",pwd);
    settings_setpwd.setValue("/database/changepassword",0);
}

void Widget::DecryPassWord()
{
    password = XorEncryptDecrypt(password,12);
}

Widget::~Widget()
{
    delete ui;
    gwdb.close();
}

void Widget::timeupdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    int currenthour = QTime::currentTime().hour();
    int currentminute = QTime::currentTime().minute();
    QString marketstatus;
    if(currenthour < 9 ||
      (currenthour == 9 && currentminute < 30) ||
       currenthour >= 15)
    {
        marketstatus = "        闭市";
    }
    else if((currenthour == 9 && currentminute > 29) ||
            (currenthour > 9 && currenthour < 11) ||
            (currenthour == 11 && currentminute < 30) ||
            (currenthour >=13 && currenthour <15))
    {
        marketstatus = "        开市";
    }
    str.append(marketstatus);
    ui->label->setText(str);

}

void Widget::connectgwdatabase()
{
    gwdb = QSqlDatabase::addDatabase("QOCI");
    gwdb.setHostName(ip);
    gwdb.setDatabaseName(instance);
    gwdb.setUserName(user);
    gwdb.setPassword(password);
    bool ok=gwdb.open();
    if(ok)
    {
        qDebug()<<"open database success";
    }
    else
    {
        qDebug()<<"error open database because"<<gwdb.lastError().text();
        QMessageBox msgBox;
        msgBox.setText(gwdb.lastError().text());
        msgBox.exec();
    }
}
//现货委托金额和委托笔数
void Widget::query_xh_orderamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select sum(1),sum(case when o.stktype in ('A4','C3')  then (100* o.orderqty) else (o.orderprice* o.orderqty) end) as price from openorder o  where o.withdrawflag = 'F'";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int orderqty = query.value(0).toInt();
       float orderamt = query.value(1).toFloat();
       ui->lcdNumber->setDigitCount(8);
       ui->lcdNumber_2->setDigitCount(8);
       ui->lcdNumber->display(orderamt/10000);
       ui->lcdNumber_2->display(orderqty);
    }
}
//期货委托金额和委托笔数
void Widget::query_qh_orderamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select sum(1), sum(o.futureorderprice * o.orderqty * fi.contracttimes)"
            " from futureopenorder o, futureinfo fi"
            " where o.f_productid = fi.f_productid"
            " and o.stkid = fi.stkid"
            " and fi.stktype = '0'"
            " and UPPER(o.actionflag) = 'NEW'";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int orderqty = query.value(0).toInt();
       float orderamt = query.value(1).toFloat();
       ui->lcdNumber_3->setDigitCount(8);
       ui->lcdNumber_4->setDigitCount(8);
       ui->lcdNumber_4->display(orderqty);
       ui->lcdNumber_3->display(orderamt/10000);
    }
}
//期权委托金额和委托笔数
void Widget::query_qq_orderamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select sum(1), sum(o.futureorderprice * o.orderqty * fi.contracttimes)"
            " from futureopenorder o, futureinfo fi"
            " where o.f_productid = fi.f_productid"
            " and o.stkid = fi.stkid"
            " and fi.stktype in ('3','4')"
            " and UPPER(o.actionflag) = 'NEW'";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int orderqty = query.value(0).toInt();
       float orderamt = query.value(1).toFloat();
       ui->lcdNumber_5->setDigitCount(8);
       ui->lcdNumber_6->setDigitCount(8);
       ui->lcdNumber_6->display(orderqty);
       ui->lcdNumber_5->display(orderamt/10000);
    }
}
//现货委托速度峰值及时间点
void Widget::query_xh_orderspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
            " from (select occurtime, sum(1) cnt"
            " from openorder o"
            " group by occurtime"
            " order by sum(1) desc)"
            "  where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();

       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_10->setDigitCount(8);
       ui->lcdNumber_7->setDigitCount(8);
       ui->lcdNumber_7->display(speed_max);
       ui->lcdNumber_10->display(showtime);
    }
}
//期货委托速度峰值及时间点
void Widget::query_qh_orderspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
                   " from (select fp.occurtime, sum(1) cnt"
                   " from futureopenorder fp, futureinfo fi"
                   " where fp.f_productid = fi.f_productid"
                   " and fp.stkid = fi.stkid"
                   "  and fi.stktype = '0'"
                   "  and substr(fp.occurtime,9,4)<1600"
                   " group by fp.occurtime"
                   " order by sum(1) desc)"
                   " where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();
       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_11->setDigitCount(8);
       ui->lcdNumber_8->setDigitCount(8);
       ui->lcdNumber_8->display(speed_max);
       ui->lcdNumber_11->display(showtime);
    }
}
//期权委托速度峰值及时间点
void Widget::query_qq_orderspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
            " from (select fp.occurtime, sum(1) cnt"
            " from futureopenorder fp, futureinfo fi"
            " where fp.f_productid = fi.f_productid"
            "  and fp.stkid = fi.stkid"
            "  and fi.stktype in ('3','4')"
            " group by fp.occurtime"
            " order by sum(1) desc)"
            " where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();
       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_12->setDigitCount(8);
       ui->lcdNumber_9->setDigitCount(8);
       ui->lcdNumber_9->display(speed_max);
       ui->lcdNumber_12->display(showtime);
    }
}
//现货成交金额和成交笔数
void Widget::query_xh_matchamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="SELECT COUNT (dcon) as a, SUM (dfullknockamt) as b"
                         " FROM (SELECT   contractnum dcon, SUBSTR (t.occurtime, 8) tdate,"
                         " SUM (fullknockamt) dfullknockamt"
                         " FROM tradingresult t"
                         " WHERE t.exchid IN ('0', '1')"
                         " AND t.ordertype != '0C'"
                         " AND t.tradingresulttype LIKE '0%'"
                         " AND t.knockamt <> 0 "
                         " GROUP BY contractnum, SUBSTR (t.occurtime, 8))";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int matchqty = query.value(0).toInt();
       float matchamt = query.value(1).toFloat();
       ui->lcdNumber_28->setDigitCount(8);
       ui->lcdNumber_29->setDigitCount(8);
       ui->lcdNumber_28->display(matchamt/10000);
       ui->lcdNumber_29->display(matchqty);
    }
}
//期货成交金额和成交笔数
void Widget::query_qh_matchamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select sum(1), nvl(sum(abs(o.knockamt)),0)"
            " from futuretradingresult o, futureinfo fi"
            " where o.f_productid = fi.f_productid"
            " and o.stkid = fi.stkid"
            " and fi.stktype = '0'";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int matchqty = query.value(0).toInt();
       float matchamt = query.value(1).toFloat();
       ui->lcdNumber_30->setDigitCount(8);
       ui->lcdNumber_31->setDigitCount(8);
       ui->lcdNumber_30->display(matchamt/10000);
       ui->lcdNumber_31->display(matchqty);
    }
}
//期权成交金额和成交笔数
void Widget::query_qq_matchamtandqty()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select sum(1), nvl(sum(abs(o.knockamt)),0)"
            " from futuretradingresult o, futureinfo fi"
            " where o.f_productid = fi.f_productid"
            "  and o.stkid = fi.stkid"
            "  and fi.stktype in ('3','4')";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int matchqty = query.value(0).toInt();
       float matchamt = query.value(1).toFloat();
       ui->lcdNumber_32->setDigitCount(8);
       ui->lcdNumber_33->setDigitCount(8);
       ui->lcdNumber_32->display(matchamt/10000);
       ui->lcdNumber_33->display(matchqty);
    }
}
//现货成交峰值及出现时间点
void Widget::query_xh_matchspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
            " from (select occurtime, sum(1) cnt"
            " from tradingresult o"
            " group by occurtime"
            " order by sum(1) desc)"
            " where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();
       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_14->setDigitCount(8);
       ui->lcdNumber_13->setDigitCount(8);
       ui->lcdNumber_13->display(speed_max);
       ui->lcdNumber_14->display(showtime);
    }
}
//期货成交峰值及出现时间点
void Widget::query_qh_matchspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
            " from (select fp.occurtime, sum(1) cnt"
            " from futuretradingresult fp, futureinfo fi"
            " where fp.f_productid = fi.f_productid"
            " and fp.stkid = fi.stkid"
            " and fi.stktype = '0'"
            " and substr(fp.occurtime,9,4)<1600"
            " group by fp.occurtime"
            " order by sum(1) desc)"
            " where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();
       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_16->setDigitCount(8);
       ui->lcdNumber_15->setDigitCount(8);
       ui->lcdNumber_15->display(speed_max);
       ui->lcdNumber_16->display(showtime);
    }
}
//期权成交峰值及出现时间点
void Widget::query_qq_matchspeedmax()
{
    QSqlQuery query(gwdb);
    QString sql_orderrec="select decode(count(cnt), 0, '19700101000000', max(occurtime)) peakTime,decode(count(cnt),0,0,max(cnt) ) ct"
            " from (select fp.occurtime, sum(1) cnt"
            " from futuretradingresult fp, futureinfo fi"
            " where fp.f_productid = fi.f_productid"
            " and fp.stkid = fi.stkid"
            " and fi.stktype in ('3','4')"
            " group by fp.occurtime"
            " order by sum(1) desc)"
            " where rownum = 1";
    query.exec(sql_orderrec);
    if (query.next())
    {
       int speed_max = query.value(1).toInt();
       QString max_time = query.value(0).toString();
       QString max_hour = max_time.mid(8,2);
       QString max_minute = max_time.mid(10,2);
       QString max_second = max_time.mid(12,2);
       QString showtime = max_hour.append(":").append(max_minute).append(":").append(max_second);
       ui->lcdNumber_18->setDigitCount(8);
       ui->lcdNumber_17->setDigitCount(8);
       ui->lcdNumber_17->display(speed_max);
       ui->lcdNumber_18->display(showtime);
    }
}
void Widget::query_xh_azps()
{
    QString azpslog = Currentpath;
    azpslog.append("/log/");
    azpslog.append(QDate::currentDate().toString("yyyyMMdd"));
    azpslog.append("azps.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_azps_Count = 0;
    static int upThreshold_azps_Count = 0;
    static int closealert_azps = 0;
    static int closealert_azps_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/azps",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/azps",60).toInt();
    int uplengtime = settings.value("/uplengtime/azps",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) as flag from quotaorder where sendflag = '0' and offertime = '-1'";
    query.exec(sql_orderrec);
    QFile file(azpslog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count <= threshold )
       {
           lowThreshold_azps_Count++;
       }
       else
       {
           lowThreshold_azps_Count = 0;
       }
       if(order_count >threshold)
       {
           upThreshold_azps_Count++;
       }
       else
       {
           upThreshold_azps_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_azps_Count >0)
           {
               if(closealert_azps < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_azps++;
               }
               logmessage = "触发阈值立刻报警，当前按值配售数量为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_19->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_azps = 0;
               ui->lcdNumber_19->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_azps_Count >= uplengtime/refresh[0])
           {
               if(closealert_azps < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_azps++;
               }
               logmessage = "按值配售笔数达到";
               logmessage.append(QString::number(threshold));
               logmessage.append("笔已经持续了");
               logmessage.append(QString::number(uplengtime));
               logmessage.append("秒");
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_19->setStyleSheet("background-color:red;");
           }
           else if(lowThreshold_azps_Count >= lowlengtime/refresh[0])
           {
               QString sql_query=QString("select count(*) as flag from quotaorder where sendflag = '0' and offertime = '-1'"
                       " and (Sysdate - To_Date(OCCURTIME, 'yyyymmddhh24miss'))* 24 * 60 * 60 > %1").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_azps_low < alertcount)
                      { 
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_azps_low++;
                      }
                      logmessage = "至少有一笔按值配售数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_19->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_19->setStyleSheet("background-color:#123B79;");
                      closealert_azps_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_19->setStyleSheet("background-color:#123B79;");
               closealert_azps = 0;
               closealert_azps_low = 0;
           }
       }
       ui->lcdNumber_19->display(order_count);
    }
    file.flush();
    file.close();
}
void Widget::query_xh_hssscj()
{
    QString hssscjlog = Currentpath;
    hssscjlog.append("/log/");
    hssscjlog.append(QDate::currentDate().toString("yyyyMMdd"));
    hssscjlog.append("hssscj.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_hssscj_Count = 0;
    static int upThreshold_hssscj_Count = 0;
    static int closealert_hssscj = 0;
    static int closealert_hssscj_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/hssscj",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/hssscj",60).toInt();
    int uplengtime = settings.value("/uplengtime/hssscj",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) as flag from TRADINGRESULTERRORS where substr(occurtime,0,8)=to_char(sysdate,'YYYYMMDD')";
    query.exec(sql_orderrec);
    QFile file(hssscjlog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count <= threshold )
       {
           lowThreshold_hssscj_Count++;
       }
       else
       {
           lowThreshold_hssscj_Count = 0;
       }
       if(order_count >threshold)
       {
           upThreshold_hssscj_Count++;
       }
       else
       {
           upThreshold_hssscj_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_hssscj_Count >0)
           {
               if(closealert_hssscj < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_hssscj++;
               }
               logmessage = "触发阈值立刻报警，当前回扫实时成交笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_20->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_hssscj = 0;
               ui->lcdNumber_20->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_hssscj_Count >= uplengtime/refresh[1])
           {
               if(closealert_hssscj < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_hssscj++;
               }
               logmessage = "回扫实时成交笔数达到";
               logmessage.append(QString::number(threshold));
               logmessage.append("笔已经持续了");
               logmessage.append(QString::number(uplengtime));
               logmessage.append("秒");
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_20->setStyleSheet("background-color:red;");
           }
           else if(lowThreshold_hssscj_Count >= lowlengtime/refresh[1])
           {
               QString sql_query=QString(" select count(*) as flag from TRADINGRESULTERRORS"
                                         " where (Sysdate - To_Date(OCCURTIME, 'yyyymmddhh24miss'))* 24 * 60 * 60 > %1").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_hssscj_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_hssscj_low++;
                      }
                      logmessage = "至少有一笔实时回扫成交数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_20->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_20->setStyleSheet("background-color:#123B79;");
                      closealert_hssscj_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_20->setStyleSheet("background-color:#123B79;");
               closealert_hssscj = 0;
               closealert_hssscj_low = 0;
           }
       }
       ui->lcdNumber_20->display(order_count);
    }
    file.flush();
    file.close();

}
void Widget::query_xh_cdqr()
{
    QString cdqrlog = Currentpath;
    cdqrlog.append("/log/");
    cdqrlog.append(QDate::currentDate().toString("yyyyMMdd"));
    cdqrlog.append("cdqr.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_cdqr_Count = 0;
    static int upThreshold_cdqr_Count = 0;
    static int closealert_cdqr = 0;
    static int closealert_cdqr_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/cdqr",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/cdqr",60).toInt();
    int uplengtime = settings.value("/uplengtime/cdqr",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) as flag from (select  (SYSDATE - TO_DATE(min(b.orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60  as timeflag) "
            " from openorder a, openorder b"
            " where a.withdrawflag = 'F' and a.STKID != 'NULL' and a.tradeType != 'A9'"
            " and a.sendflag = 1 and a.validflag = 0 and (a.knockqty + a.withdrawqty) < a.orderqty"
            " and a.withdraworderflag = 1 and a.stkid = b.stkId and a.exchid = b.exchid"
            " and a.contractnum = b.contractnum and b.withdrawflag = 'T') a where a.timeflag > 30";
    query.exec(sql_orderrec);
    QFile file(cdqrlog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_cdqr_Count++;
       }
       else
       {
           lowThreshold_cdqr_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_cdqr_Count++;
       }
       else
       {
           upThreshold_cdqr_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_cdqr_Count >0)
           {
               if(closealert_cdqr < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_cdqr++;
               }
               logmessage = "触发阈值立刻报警，当前三次撤单返回确认超时30秒的笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_21->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_cdqr = 0;
               ui->lcdNumber_21->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_cdqr_Count >= uplengtime/refresh[2])
           {
               QString sql_upquery=QString(" select count(*) as flag from (select  (SYSDATE - TO_DATE(min(b.orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60  as timeflag) "
                                         " from openorder a, openorder b"
                                         " where a.withdrawflag = 'F' and a.STKID != 'NULL' and a.tradeType != 'A9'"
                                         " and a.sendflag = 1 and a.validflag = 0 and (a.knockqty + a.withdrawqty) < a.orderqty"
                                         " and a.withdraworderflag = 1 and a.stkid = b.stkId and a.exchid = b.exchid"
                                         " and a.contractnum = b.contractnum and b.withdrawflag = 'T') a where a.timeflag > (30 + %1)").arg(uplengtime);
               query.exec(sql_upquery);
               if (query.next())
               {
                   int order_upcount = query.value(0).toInt();
                   if(order_upcount >= threshold)
                   {
                       if(closealert_cdqr < alertcount)
                       {
                           if(IfAlarm())
                           {
                               QSound::play(VidioPath);
                           }
                           closealert_cdqr++;
                       }
                       logmessage = "三次撤单确认笔数达到";
                       logmessage.append(QString::number(threshold));
                       logmessage.append("笔已经持续了");
                       logmessage.append(QString::number(uplengtime));
                       logmessage.append("秒");
                       text_stream << logmessage << "\r\n";
                       ui->lcdNumber_21->setStyleSheet("background-color:red;");
                   }
               }
           }
           else if(lowThreshold_cdqr_Count >= lowlengtime/refresh[2])
           {
               QString sql_query=QString(" select count(*) as flag from (select  (SYSDATE - TO_DATE(min(b.orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60  as timeflag) "
                                         " from openorder a, openorder b"
                                         " where a.withdrawflag = 'F' and a.STKID != 'NULL' and a.tradeType != 'A9'"
                                         " and a.sendflag = 1 and a.validflag = 0 and (a.knockqty + a.withdrawqty) < a.orderqty"
                                         " and a.withdraworderflag = 1 and a.stkid = b.stkId and a.exchid = b.exchid"
                                         " and a.contractnum = b.contractnum and b.withdrawflag = 'T') a where a.timeflag > (30 + %1)").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_cdqr_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                               QSound::play(VidioPath);
                          }
                          closealert_cdqr_low++;
                      }
                      logmessage = "至少有一笔三次撤单确认数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_21->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_21->setStyleSheet("background-color:#123B79;");
                      closealert_cdqr_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_21->setStyleSheet("background-color:#123B79;");
               closealert_cdqr = 0;
               closealert_cdqr_low = 0;
           }
       }
       ui->lcdNumber_21->display(order_count);
    }
    file.flush();
    file.close();
}
void Widget::query_xh_xhwtqr()
{
    QString xhwtqrlog = Currentpath;
    xhwtqrlog.append("/log/");
    xhwtqrlog.append(QDate::currentDate().toString("yyyyMMdd"));
    xhwtqrlog.append("xhwtqr.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_xhwtqr_Count = 0;
    static int upThreshold_xhwtqr_Count = 0;
    static int closealert_xhwtqr = 0;
    static int closealert_xhwtqr_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/xhwtqr",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/xhwtqr",60).toInt();
    int uplengtime = settings.value("/uplengtime/xhwtqr",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) from (Select (Sysdate - To_Date(Min(Occurtime), 'yyyymmddhh24miss')) * 24 * 60 * 60 As timeflag from Openorder"
            " Where Exchid In ('0', '1', '3') And Sendflag = 1 And Validflag = -1 And Substr(To_Char(Ordertime), 9, 6) Not Between 113001 And 130010) a where a.timeflag > 30";
    query.exec(sql_orderrec);
    QFile file(xhwtqrlog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_xhwtqr_Count++;
       }
       else
       {
           lowThreshold_xhwtqr_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_xhwtqr_Count++;
       }
       else
       {
           upThreshold_xhwtqr_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_xhwtqr_Count >0)
           {
               if(closealert_xhwtqr < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_xhwtqr++;
               }
               logmessage = "触发阈值立刻报警，当前现货委托确认超时30秒的笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_22->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_xhwtqr = 0;
               ui->lcdNumber_22->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_xhwtqr_Count >= uplengtime/refresh[3])
           {
               QString sql_upquery=QString(" select count(*) from (Select (Sysdate - To_Date(Min(Occurtime), 'yyyymmddhh24miss')) * 24 * 60 * 60 As timeflag from Openorder"
                                           " Where Exchid In ('0', '1', '3') And Sendflag = 1 And Validflag = -1 And Substr(To_Char(Ordertime), 9, 6) Not Between 113001 And 130010) a where a.timeflag > (30 + %1)").arg(uplengtime);
               query.exec(sql_upquery);
               if (query.next())
               {
                   int order_upcount = query.value(0).toInt();
                   if(order_upcount >= threshold)
                   {
                       if(closealert_xhwtqr < alertcount)
                       {
                           if(IfAlarm())
                           {
                               QSound::play(VidioPath);
                           }
                           closealert_xhwtqr++;
                       }
                       logmessage = "现货委托未报数据达到";
                       logmessage.append(QString::number(threshold));
                       logmessage.append("笔已经持续了");
                       logmessage.append(QString::number(uplengtime));
                       logmessage.append("秒");
                       text_stream << logmessage << "\r\n";
                       ui->lcdNumber_22->setStyleSheet("background-color:red;");
                   }
               }
           }
           else if(lowThreshold_xhwtqr_Count >= lowlengtime/refresh[3])
           {
               QString sql_query=QString(" select count(*) from (Select (Sysdate - To_Date(Min(Occurtime), 'yyyymmddhh24miss')) * 24 * 60 * 60 As timeflag from Openorder"
                                         " Where Exchid In ('0', '1', '3') And Sendflag = 1 And Validflag = -1 And Substr(To_Char(Ordertime), 9, 6) Not Between 113001 And 130010) a where a.timeflag > (30 + %1)").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_xhwtqr_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                                QSound::play(VidioPath);
                          }
                          closealert_xhwtqr_low++;
                      }
                      logmessage = "至少有一笔现货委托确认数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_22->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_22->setStyleSheet("background-color:#123B79;");
                      closealert_xhwtqr_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_22->setStyleSheet("background-color:#123B79;");
               closealert_xhwtqr = 0;
               closealert_xhwtqr_low = 0;
           }
       }
       ui->lcdNumber_22->display(order_count);
    }
    file.flush();
    file.close();
}
void Widget::query_xh_xhwtwb()
{
    QString xhwtwblog = Currentpath;
    xhwtwblog.append("/log/");
    xhwtwblog.append(QDate::currentDate().toString("yyyyMMdd"));
    xhwtwblog.append("xhwtwb.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_xhwtwb_Count = 0;
    static int upThreshold_xhwtwb_Count = 0;
    static int closealert_xhwtwb = 0;
    static int closealert_xhwtwb_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/xhwtwb",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/xhwtwb",60).toInt();
    int uplengtime = settings.value("/uplengtime/xhwtwb",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="Select Count(*) as flag, a.deskid From Openorder a "
            " Where Offertime = -1 and a.orderqty <> a.withdrawqty+a.knockqty and a.withdrawflag ='F' and"
            " (sysdate-to_date(a.orderTime,'yyyymmddhh24miss'))*24*60*60 > 5";
    query.exec(sql_orderrec);
    QFile file(xhwtwblog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    QString seats = "委托未报席位:";
    int order_count = 0;
    while(query.next())
    {
        order_count = query.value(0).toInt();
        QString seat = query.value(1).toString();
        seats.append(seat);
        seats.append(" | ");
    }

    if( order_count >0 && order_count < threshold )
    {
        lowThreshold_xhwtwb_Count++;
    }
    else
    {
        lowThreshold_xhwtwb_Count = 0;
    }
    if(order_count >= threshold)
    {
        upThreshold_xhwtwb_Count++;
    }
    else
    {
        upThreshold_xhwtwb_Count = 0;
    }
    if(uplengtime == -1)//触发阈值直接告警
    {
        if(upThreshold_xhwtwb_Count >0)
        {
            if(closealert_xhwtwb < alertcount)
            {
                if(IfAlarm())
                {
                    QSound::play(VidioPath);
                }
                closealert_xhwtwb++;
            }
            logmessage = "触发阈值立刻报警，当前现货委托未报超时30秒的笔数为:";
            logmessage.append(QString::number(order_count));
            text_stream << logmessage << "\r\n";
            ui->lcdNumber_23->setStyleSheet("background-color:red;");
        }
        else
        {
            closealert_xhwtwb = 0;
            ui->lcdNumber_23->setStyleSheet("background-color:#123B79;");
        }
    }
    else //触发阈值持续一段时间后告警
    {
        if(upThreshold_xhwtwb_Count >= uplengtime/refresh[4])
        {
            QString sql_upquery=QString(" Select Count(*) as flag From Openorder a "
                                        " Where Offertime = -1 and a.orderqty <> a.withdrawqty+a.knockqty and a.withdrawflag ='F' and"
                                        " (sysdate-to_date(a.orderTime,'yyyymmddhh24miss'))*24*60*60 > (5 + %1)").arg(uplengtime);
            query.exec(sql_upquery);
            if (query.next())
            {
                int order_upcount = query.value(0).toInt();
                if(order_upcount >= threshold)
                {
                    if(closealert_xhwtwb < alertcount)
                    {
                        if(IfAlarm())
                        {
                            QSound::play(VidioPath);
                        }
                        closealert_xhwtwb++;
                    }
                    logmessage = "现货委托未报笔数达到";
                    logmessage.append(QString::number(threshold));
                    logmessage.append("笔已经持续了");
                    logmessage.append(QString::number(uplengtime));
                    logmessage.append("秒");
                    text_stream << logmessage << "\r\n";
                    ui->lcdNumber_23->setStyleSheet("background-color:red;");
                }
            }
        }
        else if(lowThreshold_xhwtwb_Count >= lowlengtime/refresh[4])
        {
            QString sql_query=QString(" Select Count(*) as flag From Openorder a "
                                      " Where Offertime = -1 and a.orderqty <> a.withdrawqty+a.knockqty and a.withdrawflag ='F' and"
                                      " (sysdate-to_date(a.orderTime,'yyyymmddhh24miss'))*24*60*60 > (5 + %1)").arg(lowlengtime);
            query.exec(sql_query);
            if (query.next())
            {
               int order_count = query.value(0).toInt();
               if(order_count>0)
               {
                   if(closealert_xhwtwb_low < alertcount)
                   {
                       if(IfAlarm())
                       {
                           QSound::play(VidioPath);
                       }
                       closealert_xhwtwb_low++;
                   }
                   logmessage = "至少有一笔现货委托未报数据已持续";
                   logmessage.append(QString::number(lowlengtime));
                   logmessage.append("秒");
                   text_stream << logmessage << "\r\n";
                   ui->lcdNumber_23->setStyleSheet("background-color:orange;");
               }
               else
               {
                   ui->lcdNumber_23->setStyleSheet("background-color:#123B79;");
                   closealert_xhwtwb_low =0;
               }
            }
        }
        else
        {
            ui->lcdNumber_23->setStyleSheet("background-color:#123B79;");
            closealert_xhwtwb = 0;
            closealert_xhwtwb_low = 0;
        }
    }
    ui->lcdNumber_23->display(order_count);
    ui->label_48->setText(seats);
    file.flush();
    file.close();
}
void Widget::query_xh_sccd()
{
    QString sccdlog = Currentpath;
    sccdlog.append("/log/");
    sccdlog.append(QDate::currentDate().toString("yyyyMMdd"));
    sccdlog.append("sccd.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_sccd_Count = 0;
    static int upThreshold_sccd_Count = 0;
    static int closealert_sccd = 0;
    static int closealert_sccd_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/sccd",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/sccd",60).toInt();
    int uplengtime = settings.value("/uplengtime/sccd",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select  nvl(max(count(*)),0) as flag From openorder o "
            " where o.withdrawflag ='T' group by o.contractnum having (count(*) > 3) "
            " and o.contractnum not in (select distinct oo.contractnum from openorder oo where oo.orderqty = oo.withdrawqty + oo.knockqty)";
    query.exec(sql_orderrec);
    QFile file(sccdlog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_sccd_Count++;
       }
       else
       {
           lowThreshold_sccd_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_sccd_Count++;
       }
       else
       {
           upThreshold_sccd_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_sccd_Count >0)
           {
               if(closealert_sccd < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_sccd++;
               }
               logmessage = "触发阈值立刻报警，当前三次撤单笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_24->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_sccd = 0;
               ui->lcdNumber_24->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_sccd_Count >= uplengtime/refresh[5])
           {
               if(closealert_sccd < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_sccd++;
               }
               logmessage = "三次撤单笔数达到";
               logmessage.append(QString::number(threshold));
               logmessage.append("笔已经持续了");
               logmessage.append(QString::number(uplengtime));
               logmessage.append("秒");
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_24->setStyleSheet("background-color:red;");
           }
           else if(lowThreshold_sccd_Count >= lowlengtime/refresh[5])
           {
               QString sql_query=QString(" select  nvl(max(count(*)),0) as flag From openorder o "
                                         " where o.withdrawflag ='T' group by o.contractnum having (count(*) > 0) "
                                         " and o.contractnum not in (select distinct oo.contractnum from openorder oo where oo.orderqty = oo.withdrawqty + oo.knockqty)"
                                         " and (sysdate-to_date(o.Occurtime,'yyyymmddhh24miss'))*24*60*60 > %1 ").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_sccd_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_sccd_low++;
                      }

                      logmessage = "至少有一笔三次撤单数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_24->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_24->setStyleSheet("background-color:#123B79;");
                      closealert_sccd_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_24->setStyleSheet("background-color:#123B79;");
               closealert_sccd = 0;
               closealert_sccd_low = 0;
           }
       }
       ui->lcdNumber_24->display(order_count);
    }
    file.flush();
    file.close();
}
void Widget::query_xh_qhwtwb()
{
    QString qhwtwblog = Currentpath;
    qhwtwblog.append("/log/");
    qhwtwblog.append(QDate::currentDate().toString("yyyyMMdd"));
    qhwtwblog.append("qhwtwb.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_qhwtwb_Count = 0;
    static int upThreshold_qhwtwb_Count = 0;
    static int closealert_qhwtwb = 0;
    static int closealert_qhwtwb_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/qhwtwb",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/qhwtwb",60).toInt();
    int uplengtime = settings.value("/uplengtime/qhwtwb",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) as flag from futureopenorder"
                         " where sendflag = 0 and offertime = -1";
    query.exec(sql_orderrec);
    QFile file(qhwtwblog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_qhwtwb_Count++;
       }
       else
       {
           lowThreshold_qhwtwb_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_qhwtwb_Count++;
       }
       else
       {
           upThreshold_qhwtwb_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_qhwtwb_Count >0)
           {
               if(closealert_qhwtwb < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_qhwtwb++;
               }
               logmessage = "触发阈值立刻报警，当前期货委托未报笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_25->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_qhwtwb = 0;
               ui->lcdNumber_25->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_qhwtwb_Count >= uplengtime/refresh[6])
           {
               QString sql_upquery=QString(" select count(*) as flag from futureopenorder"
                                           " where sendflag = 0 and offertime = -1 and"
                                           " (sysdate-to_date(Occurtime,'yyyymmddhh24miss'))*24*60*60 > %1").arg(uplengtime);
               query.exec(sql_upquery);
               if (query.next())
               {
                   int order_upcount = query.value(0).toInt();
                   if(order_upcount >= threshold)
                   {
                       if(closealert_qhwtwb < alertcount)
                       {
                           if(IfAlarm())
                           {
                               QSound::play(VidioPath);
                           }
                           closealert_qhwtwb++;
                       }
                       logmessage = "期货委托未报笔数达到";
                       logmessage.append(QString::number(threshold));
                       logmessage.append("笔已经持续了");
                       logmessage.append(QString::number(uplengtime));
                       logmessage.append("秒");
                       text_stream << logmessage << "\r\n";
                       ui->lcdNumber_25->setStyleSheet("background-color:red;");
                   }
               }
           }
           else if(lowThreshold_qhwtwb_Count >= lowlengtime/refresh[6])
           {
               QString sql_query=QString(" select count(*) as flag from futureopenorder"
                                         " where sendflag = 0 and offertime = -1 and"
                                         " (sysdate-to_date(Occurtime,'yyyymmddhh24miss'))*24*60*60 > %1").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_qhwtwb_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_qhwtwb_low++;
                      }
                      logmessage = "至少有一笔期货委托未报数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_25->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_25->setStyleSheet("background-color:#123B79;");
                      closealert_qhwtwb_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_25->setStyleSheet("background-color:#123B79;");
               closealert_qhwtwb = 0;
               closealert_qhwtwb_low = 0;
           }
       }
       ui->lcdNumber_25->display(order_count);
    }
    file.flush();
    file.close();
}
void Widget::query_xh_qhwtfs()
{
    QString qhwtfslog = Currentpath;
    qhwtfslog.append("/log/");
    qhwtfslog.append(QDate::currentDate().toString("yyyyMMdd"));
    qhwtfslog.append("qhwtfs.txt");
    //达不到阈值时如果长期存在大于1笔的单，则告警
    static int lowThreshold_qhwtfs_Count = 0;
    static int upThreshold_qhwtfs_Count = 0;
    static int closealert_qhwtfs = 0;
    static int closealert_qhwtfs_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/qhwtfs",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/qhwtfs",60).toInt();
    int uplengtime = settings.value("/uplengtime/qhwtfs",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*) as flag from (select  (SYSDATE - TO_DATE(min(orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60 as timeflag"
                         "  from futureopenorder"
                         "  where sendflag in ('0','8','9')"
                         "  and LOCALORDERID is null) a where a.timeflag > 30";
    query.exec(sql_orderrec);
    QFile file(qhwtfslog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_qhwtfs_Count++;
       }
       else
       {
           lowThreshold_qhwtfs_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_qhwtfs_Count++;
       }
       else
       {
           upThreshold_qhwtfs_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_qhwtfs_Count >0)
           {
               if(closealert_qhwtfs < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_qhwtfs++;
               }
               logmessage = "触发阈值立刻报警，当前期货委托发送时间差超时30秒的笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_26->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_qhwtfs = 0;
               ui->lcdNumber_26->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_qhwtfs_Count >= uplengtime/refresh[7])
           {
               QString sql_upquery=QString(" select count(*) as flag from (select  (SYSDATE - TO_DATE(min(orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60 as timeflag"
                                           "  from futureopenorder"
                                           "  where sendflag in ('0','8','9')"
                                           "  and LOCALORDERID is null) a where a.timeflag > (30 + %1)").arg(uplengtime);
               query.exec(sql_upquery);
               if (query.next())
               {
                   int order_upcount = query.value(0).toInt();
                   if(order_upcount >= threshold)
                   {
                       if(closealert_qhwtfs < alertcount)
                       {
                           if(IfAlarm())
                           {
                               QSound::play(VidioPath);
                           }
                           closealert_qhwtfs++;
                       }
                       logmessage = "期货委托发送时间差持续了";
                       logmessage.append(QString::number(uplengtime));
                       logmessage.append("秒的，目前有");
                       logmessage.append(QString::number(threshold));
                       logmessage.append("笔");
                       text_stream << logmessage << "\r\n";
                       ui->lcdNumber_26->setStyleSheet("background-color:red;");
                   }
               }
           }
           else if(lowThreshold_qhwtfs_Count >= lowlengtime/refresh[7])
           {
               QString sql_query=QString(" select count(*) as flag from (select  (SYSDATE - TO_DATE(min(orderTime), 'yyyymmddhh24miss')) * 24 * 60 * 60 as timeflag"
                                         "  from futureopenorder"
                                         "  where sendflag in ('0','8','9')"
                                         "  and LOCALORDERID is null) a where a.timeflag > (30 + %1)").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_qhwtfs_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_qhwtfs_low++;
                      }
                      logmessage = "至少有一笔实时回扫成交数据已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_26->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_26->setStyleSheet("background-color:#123B79;");
                      closealert_qhwtfs_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_26->setStyleSheet("background-color:#123B79;");
               closealert_qhwtfs = 0;
               closealert_qhwtfs_low = 0;
           }
       }
       ui->lcdNumber_26->display(order_count);
    }
    file.flush();
    file.close();

}
void Widget::query_xh_qhwtsb()
{
    QString qhwtsblog = Currentpath;
    qhwtsblog.append("/log/");
    qhwtsblog.append(QDate::currentDate().toString("yyyyMMdd"));
    qhwtsblog.append("qhwtsb.txt");
    static int lowThreshold_qhwtsb_Count = 0;
    static int upThreshold_qhwtsb_Count = 0;
    static int closealert_qhwtsb = 0;
    static int closealert_qhwtsb_low = 0;
    //读取配置文件获得配置
    QSettings settings(iniPath,QSettings::IniFormat);
    int threshold = settings.value("/threshold/qhwtsb",2).toInt();
    int lowlengtime = settings.value("/lowlengtime/qhwtsb",60).toInt();
    int uplengtime = settings.value("/uplengtime/qhwtsb",30).toInt();
    QSqlQuery query(gwdb);
    QString sql_orderrec="select count(*)  as flag from futureopenorder where sendflag = '7'";
    query.exec(sql_orderrec);
    QFile file(qhwtsblog);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    QString logmessage;
    if (query.next())
    {
       int order_count = query.value(0).toInt();

       if( order_count >0 && order_count < threshold )
       {
           lowThreshold_qhwtsb_Count++;
       }
       else
       {
           lowThreshold_qhwtsb_Count = 0;
       }
       if(order_count >= threshold)
       {
           upThreshold_qhwtsb_Count++;
       }
       else
       {
           upThreshold_qhwtsb_Count = 0;
       }
       if(uplengtime == -1)//触发阈值直接告警
       {
           if(upThreshold_qhwtsb_Count >0)
           {
               if(closealert_qhwtsb < alertcount)
               {
                   if(IfAlarm())
                   {
                       QSound::play(VidioPath);
                   }
                   closealert_qhwtsb++;
               }
               logmessage = "触发阈值立刻报警，当前期货委托失败笔数为:";
               logmessage.append(QString::number(order_count));
               text_stream << logmessage << "\r\n";
               ui->lcdNumber_27->setStyleSheet("background-color:red;");
           }
           else
           {
               closealert_qhwtsb = 0;
               ui->lcdNumber_27->setStyleSheet("background-color:#123B79;");
           }
       }
       else //触发阈值持续一段时间后告警
       {
           if(upThreshold_qhwtsb_Count >= uplengtime/refresh[8])
           {
               QString sql_upquery=QString(" select count(*)  as flag from futureopenorder where sendflag = '7'"
                                           "  and (sysdate-to_date(Occurtime,'yyyymmddhh24miss'))*24*60*60 > %1 ").arg(uplengtime);
               query.exec(sql_upquery);
               if (query.next())
               {
                   int order_upcount = query.value(0).toInt();
                   if(order_upcount >= threshold)
                   {
                       if(closealert_qhwtsb < alertcount)
                       {
                           if(IfAlarm())
                           {
                               QSound::play(VidioPath);
                           }
                           closealert_qhwtsb++;
                       }
                       logmessage = "期货委托发送失败笔数达到";
                       logmessage.append(QString::number(threshold));
                       logmessage.append("笔已经持续了");
                       logmessage.append(QString::number(uplengtime));
                       logmessage.append("秒");
                       text_stream << logmessage << "\r\n";
                       ui->lcdNumber_27->setStyleSheet("background-color:red;");
                   }
               }
           }
           else if(lowThreshold_qhwtsb_Count >= lowlengtime/refresh[8])
           {
               QString sql_query=QString(" select count(*)  as flag from futureopenorder where sendflag = '7'"
                                         "  and (sysdate-to_date(Occurtime,'yyyymmddhh24miss'))*24*60*60 > %1").arg(lowlengtime);
               query.exec(sql_query);
               if (query.next())
               {
                  int order_count = query.value(0).toInt();
                  if(order_count>0)
                  {
                      if(closealert_qhwtsb_low < alertcount)
                      {
                          if(IfAlarm())
                          {
                              QSound::play(VidioPath);
                          }
                          closealert_qhwtsb_low++;
                      }
                      logmessage = "至少有一笔期货委托发送失败已持续";
                      logmessage.append(QString::number(lowlengtime));
                      logmessage.append("秒");
                      text_stream << logmessage << "\r\n";
                      ui->lcdNumber_27->setStyleSheet("background-color:orange;");
                  }
                  else
                  {
                      ui->lcdNumber_27->setStyleSheet("background-color:#123B79;");
                      closealert_qhwtsb_low =0;
                  }
               }
           }
           else
           {
               ui->lcdNumber_27->setStyleSheet("background-color:#123B79;");
               closealert_qhwtsb = 0;
               closealert_qhwtsb_low = 0;
           }
       }
       ui->lcdNumber_27->display(order_count);
    }
    file.flush();
    file.close();
}

