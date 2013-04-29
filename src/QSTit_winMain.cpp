/*
    ═══════════════════════════════════════════════════════════════════════════
    This file is part of QSTit.
    Feedback, comments and questions are welcome:
    subtitles@nova-cinema.org

    QSTit is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version. If you do, we'd like to hear about it.

    QSTit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QSTit. If not, see <http://www.gnu.org/licenses/>
    ═══════════════════════════════════════════════════════════════════════════
    Free Icons by Axialis Software - Axialis Team <http://www.axialis.com>
    ═══════════════════════════════════════════════════════════════════════════
*/

#include "QSTit_winMain.h"
#include "QSTit_diaGrid.h"
#include "QSTit_diaButt.h"
#include "QSTit_diaSkin.h"

winMain::winMain()
{
    gAcce=0;            // accelerator in mls
    gAuto=false;
    gConf=false;
    #ifdef Q_OS_LINUX
    gHome = QDir::homePath();
//   QDir::mkpath(gHome+"/.config/");
//    gConfFile= gHome+"/.qstit/QSTit.cfg";
    gConfFile= gHome+"/QSTit.cfg";
    #else
    gConfFile="./QSTit.cfg";
    #endif
    gFile="";
    gLang=0;            // 0=english,1=other (from QSTit_Lang.txt)
    gManu=false;
    gPuls=100;          // basic timeout interval in mls (100/1000=0.1 sec)
    gJump=0;            // jump step
    gJumpBase=200;      // jump base
    gSett=false;
    gSrtx=false;        // true=srt,false=txt
    gVers="2.8.3";
    gWork=false;

    gBackDial=false;
    gColoDial=false;
    gExitDial=false;
    gFileDial=false;
    gFontDial=false;
    gGridDial=false;
    gGridShow=false;
    gHelpDial=false;
    gInfoDial=false;
    gOutlDial=false;
    gSettShow=false;
    gWindDial=false;

    gFileEnco=true;
    gSecoText=false;
    gSecoItal=false;
    gGridEdit=true;
    gGridSave=false;
    gGridColoDark=true;

    gWindBack="#000000";
    gRowsBack="#000000";
    gRowsColo="#ffffff";
    gOutlColo=QColor("#7f7f7f");
    gGridBack="#222222";
    gGridColo="#ffffff";
    gErroBack="#ff0000";
    gErroColo="#ffffff";

    gSystFontFami=qApp->font().family();
    gRowsFont=QFont(qApp->font().family(),22,QFont::Normal,false);
    gGridFont=QFont(qApp->font().family(),9,QFont::Normal,false);

    gGriCStyl="background-color:#222222;color:#ffffff;selection-background-color:#0055aa;selection-color:#000000;border:none;";
    gExplDisa="color:#555555;border:none;";
    gClokStyl="font:normal 11px "+gSystFontFami+";background-color:#000000;color:#ffffff;border:1px solid #000000;border-radius:3px;";
    gTimeStyl="font:normal 11px "+gSystFontFami+";background-color:#000000;color:#ffffff;border:1px solid #000000;border-radius:3px;";
    gPulsStyl="font:normal 10px "+gSystFontFami+";background-color:#000000;color:#ffffff;border:1px solid #000000;border-radius:3px;height:20px;width:20px;";
    gExplStyl="font:normal 9px "+gSystFontFami+";color:#555555;border:none;";
    gSpinStyl="height:24px;color:#ffffff;border:1px solid #777777;background-color:#eeeeee;color:#000000;";

    fApplInit();
    fWindStyle();
    fLangFileRead();
    fWindCrea();
    fMenuCrea();
    fRowsCrea();
    fRowsFramCent();
    fSettCrea();
    fGridCrea();
    fWindLogo();
    fRowsInit();
    fRowsShow(1);
    fConfRead();
}

//=================================================================================================
// application functions
//=================================================================================================

void winMain::fApplInit()
{
    objWind.widt=QApplication::desktop()->width();
    objWind.heig=QApplication::desktop()->height();
    objWind.midW=objWind.widt/2;
    objWind.midH=objWind.heig/2;
    objWind.basW=objWind.widt-2;

    objRowsNumb.mini=1;
    objRowsNumb.maxi=objRowsNumb.val0=objRowsNumb.valu=4;

    objRowsWidt.mini=100;
    objRowsWidt.maxi=objRowsWidt.val0=objRowsWidt.valu=objWind.basW;

    objRowsHeig.mini=20;
    objRowsHeig.maxi=100;
    objRowsHeig.val0=objRowsHeig.valu=30;

    objRowsSpac.mini=-10;
    objRowsSpac.maxi=200;
    objRowsSpac.val0=objRowsSpac.valu=0;

    objRowsRota.mini=-50;
    objRowsRota.maxi=50;
    objRowsRota.val0=objRowsRota.valu=0;

    objRowsOutl.mini=0;
    objRowsOutl.maxi=30;
    objRowsOutl.val0=objRowsOutl.valu=0;

    this->setGeometry(0,0,objWind.widt,objWind.heig);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

//=================================================================================================
// main window functions
//=================================================================================================

void winMain::fWindCrea()
{
    winWind=new QWidget(this,Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint);
    winWind->showFullScreen();
    this->setFixedSize(objWind.widt,objWind.heig);
    winWind->setGeometry(0,0,objWind.widt,objWind.heig);
    winWind->setContentsMargins(0,0,0,0);
    winWind->setCursor(QCursor(QPixmap(":/Imag/QSTit_curV.png"),-1,-1));
}
void winMain::fWindStyle()
{
    QString sStyl="* {background-color:#000000;color:#ffffff;border:none;}";
    sStyl+="QLabel {font:normal 11px "+gSystFontFami+";background-color:#151515;border:none;}";
    sStyl+="QSlider::groove:vertical {background-color:#0055aa;border:1px solid #222222;border-radius:6px;}";
    sStyl+="QSlider::sub-page:vertical {background-color:#222222;border:1px solid #222222;border-radius:6px;}";
    sStyl+="QSlider::handle:vertical {image:url(:/Imag/QSTit_butY.png);border:none;}";
    sStyl+="QRadioButton {border:none;min-height:16px;max-height:16px;min-width:64px;}";
    sStyl+="QRadioButton::indicator:checked {image:url(:/Imag/QSTit_butY.png);}";
    sStyl+="QRadioButton::indicator:unchecked {image:url(:/Imag/QSTit_butN.png);}";
    sStyl+="QMessageBox {background-color:#151515;color:#ffffff;border:1px solid #0055aa;border-radius:3px;}";
    sStyl+="QPushButton {min-height:20px;max-height:20px;min-width:70px;max-width:90px;background-color:#202020;color:#ffffff;border:1px solid #555555;border-radius:3px;text-align:left;padding-left:2px;}";
    sStyl+="QPushButton:hover {border-color:#0055aa;}";
    sStyl+="QTabWidget {background-color:#151515;color:#ffffff;border:none;}";
    sStyl+="QTabWidget::pane {background-color:#151515;color:#ffffff;border:none;margin:0 0 0 0;}";
    sStyl+="QTabWidget::tab-bar {background-color:#151515;color:#ffffff;}";
    sStyl+="QTabWidget::tab {border:1px solid #ffffff;border-bottom-color:#151515;margin:5px;width:70px;height:20px;}";
    sStyl+="QTabBar::tab:selected {background-color:#0055aa;color:#000000;width:70px;height:20px;margin-bottom:1px;margin-right:6px;border:1px solid #555555;border-radius:3px;}";
    sStyl+="QTabBar::tab:!selected {background-color:#151515;color:#ffffff;width:70px;height:20px;margin-bottom:1px;margin-right:6px;border:1px solid #555555;border-radius:3px;}";
    sStyl+="QTabBar::tab:hover {border-color:#0055aa;}";
    sStyl+="QTableCornerButton::section {background:#151515;border:none;border-right:1px solid #0055aa;}";
    sStyl+="QHeaderView::section:horizontal {background-color:"+gGridBack+";color:"+gGridBack+";border:none;}";
    sStyl+="QHeaderView::section:vertical {font:normal 11px "+gSystFontFami+";background:#151515;color:#0055aa;padding-left:2px;border:1px solid #0055aa;border-top:0px;border-left:0px;}";
    sStyl+="QToolTip {font:normal 11px "+gSystFontFami+";background-color:#32cd32;color:#000000;border-style:outset;border:1px solid #32cd32;padding:0px;}";
    sStyl+="QScrollBar:vertical {width:10px;background-color:#aaaaaa;margin:10 0 10 0;}";
    sStyl+="QScrollBar::handle:vertical {background-color:#777777;min-height:30px;border-radius:4px;}";
    sStyl+="QScrollBar::handle:hover {background-color:#0055aa;}";
    sStyl+="QScrollBar::add-line:vertical {background-image:url(:/Imag/QSTit_scro_down.png); height:12px; subcontrol-position:bottom;subcontrol-origin:margin;}";
    sStyl+="QScrollBar::sub-line:vertical {background-image:url(:/Imag/QSTit_scro_upup.png);height:12px;subcontrol-position:top;subcontrol-origin:margin;}";
    sStyl+="QScrollBar::add-page:vertical {background:none;}";
    sStyl+="QScrollBar::sub-page:vertical {background:none;}";
    sStyl+="QScrollBar:horizontal {height:10px;background-color:#aaaaaa;margin:0 10px 0 10px;}";
    sStyl+="QScrollBar::handle:horizontal {background-color:#777777;min-width:30px;border-radius:4px;}";
    sStyl+="QScrollBar::handle:hover {background-color:#0055aa;}";
    sStyl+="QScrollBar::add-line:horizontal {background-image: url(:/Imag/QSTit_scro_righ.png); width:12px; subcontrol-position:right;subcontrol-origin:margin;}";
    sStyl+="QScrollBar::sub-line:horizontal {background-image: url(:/Imag/QSTit_scro_left.png);width:12px;subcontrol-position:left;subcontrol-origin:margin;}";
    sStyl+="QScrollBar::add-page:horizontal {background:none;}";
    sStyl+="QScrollBar::sub-page:horizontal {background:none;}";
//    sStyl+="QProgressBar::chunk:horizontal {background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 #0055aa, stop: 1 #222222);}";
    sStyl+="QProgressBar {text-align:center;}";
    sStyl+="QProgressBar::chunk:horizontal {background-color:#0055aa;}";
    qApp->setStyleSheet(sStyl);
}
void winMain::fWindBackDial()
{
    if (gWindDial) {diaColo->close();gWindDial=false;return;}
    gWindDial=true;
    diaColo=new diaColoSkin(winWind,fraMenu,fL("diaWindBack"),gWindBack);
    connect(diaColo,SIGNAL(sClosed()),this,SLOT(fWindBackClos()));
    connect(diaColo,SIGNAL(sColorGet(QColor)),this,SLOT(fWindBackGet(QColor)));
}
void winMain::fWindBackClos() {gWindDial=false;}
void winMain::fWindBackGet(QColor cColo) {gWindDial=false;gWindBack=cColo.name();fWindBack();}
void winMain::fWindBack() {winWind->setStyleSheet("background-color:"+gWindBack+";color:#ffffff;border:none;");}
void winMain::fWindClear() {winWind->setStyleSheet("background-color:#000000;color:#ffffff;border:none;");}
void winMain::fWindTask()
{
    objWind.heig=QApplication::desktop()->height();
    if(radTaskShow->isChecked()) {objWind.heig=QApplication::desktop()->availableGeometry().height();}
    this->setFixedSize(objWind.widt,objWind.heig);
    winWind->setGeometry(0,0,objWind.widt,objWind.heig);
    fraMenu->iY=objWind.heig-fraMenu->iH-1;
    fraMenu->move(fraMenu->iX,fraMenu->iY);
    diaSett->fRePosi();
    if (gGridShow) diaGrid->fRePosi();
}
void winMain::fWindExitDial()
{
    if (gExitDial) {fWindExitCanc();return;}
    gExitDial=true;

    fGridModi();

    int iWidt=300;
    int iHeig=150;

    QString sStyl="color:#ffffff;border:none;";

    diaExit=new diaSkin(winWind,fraMenu,fL("diaExit"),iWidt,iHeig,-1,-1);
    connect(diaExit,SIGNAL(sClosed()),this,SLOT(fWindExitClos()));

    radExitSavN=new QRadioButton(fL("radExitSavN"),diaExit);
    radExitSavN->setStyleSheet(sStyl);
    radExitSavN->move(10,40);
    radExitSavN->setChecked(true);

    radExitSavP=new QRadioButton(fL("radExitSavP"),diaExit);
    radExitSavP->setStyleSheet(sStyl);
    radExitSavP->move(10,60);

    radExitSavF=new QRadioButton(fL("radExitSavF"),diaExit);
    radExitSavF->setStyleSheet(sStyl);
    radExitSavF->move(10,80);
    if (gFile.size()<=4) {radExitSavF->setStyleSheet(gExplDisa);radExitSavF->setEnabled(false);}

    butExitCanc=new QPushButton(QPixmap(":/Imag/QSTit_canc.png"),fL("butExitCanc"),diaExit);
    butExitCanc->setIconSize(QSize(16,16));
    butExitCanc->resize(70,20);
    butExitCanc->move(iWidt/2-79,110);
    connect(butExitCanc,SIGNAL(clicked()),this,SLOT(fWindExitCanc()));

    butExitExit=new QPushButton(QPixmap(":/Imag/QSTit_okok.png"),fL("butExitExit"),diaExit);
    butExitExit->setIconSize(QSize(16,16));
    butExitExit->resize(70,20);
    butExitExit->move(iWidt/2+9,110);
    connect(butExitExit,SIGNAL(clicked()),this,SLOT(fWindExit()));

    diaExit->show();
    diaExit->setFocus();
}
void winMain::fWindExitClos() {gExitDial=false;}
void winMain::fWindExitCanc() {gExitDial=false;diaExit->close();}
void winMain::fWindExit()
{
    fFileLogx();
    if (radExitSavP->isChecked()) fConfWrit(1);
    if (radExitSavF->isChecked()) fConfWrit(2);
    QApplication::quit();
}
void winMain::fWindLogo()
{
    QPixmap oLogo=QPixmap(":/Imag/QSTit_logo.png");
    labLogo=new QLabel(winWind);
    labLogo->setStyleSheet("background-color:#000000;");
    labLogo->setPixmap(oLogo);
    labLogo->move((objWind.widt-oLogo.width())/2,(objWind.heig-oLogo.height())/2);
}
void winMain::fWindLogoHide() {labLogo->setHidden(true);}
void winMain::fWindLogoFade() {if (faderWidget) faderWidget->close();faderWidget=new FaderWidget(labLogo);faderWidget->start();}

//=================================================================================================
// menu functions
//=================================================================================================

void winMain::fMenuCrea()
{
    fraMenu=new menuSkin(winWind,226,40,-1,-1);
    connect(fraMenu,SIGNAL(sMoved()),this,SLOT(fRowsStat()));

    butExit=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_exit.png"),"M"+fL("butExit"),false);
    butExit->move(fraMenu->iW-40,6);
    connect(butExit,SIGNAL(clicked()),this,SLOT(fWindExitDial()));

    butHelp=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_help_enab.png"),"M"+fL("butHelp"),false);
    butHelp->move(fraMenu->iW-80,6);
    connect(butHelp,SIGNAL(clicked()),this,SLOT(fHelpDial()));

    butFile=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_file.png"),"M"+fL("butFile"),false);
    butFile->move(fraMenu->iW-120,6);
    connect(butFile,SIGNAL(clicked()),this,SLOT(fFileDial()));

    butSett=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_sett_disa.png"),"M"+fL("butSett"),false);
    butSett->move(fraMenu->iW-160,6);
    connect(butSett,SIGNAL(clicked()),this,SLOT(fSettShow()));

    labClok=new QLabel("00:00:00",fraMenu);
    labClok->setToolTip(fL("labClok"));
    labClok->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    labClok->setStyleSheet(gClokStyl);
    labClok->setGeometry(fraMenu->iW-220,10,54,20);
    tmrClok=new QTimer(this);
    connect(tmrClok,SIGNAL(timeout()),this,SLOT(fMenuClok()));
    tmrClok->start(1000);

    butRoll=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_roll_open.png"),"L"+fL("butRoll"),false);
    butRoll->move(10,3);
    connect(butRoll,SIGNAL(clicked()),this,SLOT(fRowsShowSlot()));
    butRoll->hide();

    labTime=new QLabel("00:00:00",fraMenu);
    labTime->setToolTip(fL("labTime"));
    labTime->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    labTime->setStyleSheet(gTimeStyl);
    labTime->setGeometry(70,10,70,20);
    labTime->hide();

    butProjUpup=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_upup.png"),"L"+fL("butProjUpup"),true);
    butProjUpup->move(200,3);
    connect(butProjUpup,SIGNAL(clicked()),this,SLOT(fButtPrev()));
    butProjUpup->hide();

    butProjDown=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_down.png"),"L"+fL("butProjDown"),true);
    butProjDown->move(250,3);
    connect(butProjDown,SIGNAL(clicked()),this,SLOT(fButtNext()));
    butProjDown->hide();

    butProjPlay=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_play.png"),"R"+fL("butProjPlay"),false);
    butProjPlay->move(300,3);
    connect(butProjPlay,SIGNAL(clicked()),this,SLOT(fAutoStar()));
    butProjPlay->hide();

    butProjDece=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_dece.png"),"L"+fL("butProjDece"),true);
    butProjDece->move(380,3);
    connect(butProjDece,SIGNAL(clicked()),this,SLOT(fAutoDece()));
    butProjDece->hide();

    texPuls=new QLabel("Speed",fraMenu);
    texPuls->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    texPuls->setContentsMargins(0,0,0,0);
    texPuls->setStyleSheet(gExplStyl);
    texPuls->setGeometry(416,1,26,15);
    texPuls->hide();

    labPuls=new QLabel("",fraMenu);
    labPuls->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    labPuls->setStyleSheet(gPulsStyl);
    labPuls->setGeometry(416,16,26,20);
    labPuls->hide();

    butProjAcce=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_acce.png"),"L"+fL("butProjAcce"),true);
    butProjAcce->move(441,3);
    connect(butProjAcce,SIGNAL(clicked()),this,SLOT(fAutoAcce()));
    butProjAcce->hide();

    butProjBack=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_jump_back.png"),"L"+fL("butProjBack"),false);
    butProjBack->move(491,3);
    connect(butProjBack,SIGNAL(clicked()),this,SLOT(fAutoBack()));
    butProjBack->hide();

    texJump=new QLabel("Jump",fraMenu);
    texJump->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    texJump->setContentsMargins(0,0,0,0);
    texJump->setStyleSheet(gExplStyl);
    texJump->setGeometry(528,1,26,15);
    texJump->hide();

    labJump=new QLabel("",fraMenu);
    labJump->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    labJump->setStyleSheet(gPulsStyl);
    labJump->setGeometry(528,16,26,20);
    labJump->hide();

    butProjJump=new butToolC(fraMenu,QPixmap(":/Imag/QSTit_jump.png"),"L"+fL("butProjJump"),false);
    butProjJump->move(552,3);
    connect(butProjJump,SIGNAL(clicked()),this,SLOT(fAutoJump()));
    butProjJump->hide();
}
void winMain::fMenuAdapt(int m)                         // 0=init,1=manu,2=auto
{
    if (m==0) fraMenu->iW=226;
    else if (m==1) fraMenu->iW=364;
    else if (m==2) fraMenu->iW=717;
    fraMenu->resize(fraMenu->iW,fraMenu->iH);
    fraMenu->iX=(objWind.widt-fraMenu->iW)/2;
    fraMenu->move(fraMenu->iX,fraMenu->iY);

    int iP=fraMenu->iW;
    iP-=40;butExit->move(iP,6);
    iP-=40;butHelp->move(iP,6);
    iP-=40;butFile->move(iP,6);
    iP-=40;butSett->move(iP,6);
    iP-=60;labClok->setGeometry(iP,10,54,20);
    if (m==0)
    {
        butRoll->hide();
        labTime->hide();
        butProjUpup->hide();
        butProjDown->hide();
        butProjPlay->hide();
        butProjDece->hide();
        texPuls->hide();
        labPuls->hide();
        butProjAcce->hide();
        butProjBack->hide();
        texJump->hide();
        labJump->hide();
        butProjJump->hide();
    }
    else if (m==1)
    {
        iP=0;
        iP+=5;butRoll->move(iP,3);butRoll->show();
        labTime->hide();
        iP+=55;butProjUpup->move(iP,3);butProjUpup->show();
        iP+=40;butProjDown->move(iP,3);butProjDown->show();
        butProjPlay->hide();
        butProjDece->hide();
        texPuls->hide();
        labPuls->hide();
        butProjAcce->hide();
        butProjBack->hide();
        texJump->hide();
        labJump->hide();
        butProjJump->hide();
    }
    else if (m==2)
    {
        iP=0;
        iP+=5;butRoll->move(iP,3);butRoll->show();
        labTime->hide();
        iP+=55;butProjUpup->move(iP,3);butProjUpup->show();
        iP+=40;butProjDown->move(iP,3);butProjDown->show();
        iP+=42;labTime->setGeometry(iP,10,54,20);labTime->show();
        iP+=64;butProjPlay->move(iP,3);butProjPlay->show();
        iP+=80;butProjDece->move(iP,3);butProjDece->show();
        iP+=34;texPuls->setGeometry(iP, 1,26,15);texPuls->show();
               labPuls->setGeometry(iP,16,26,20);labPuls->show();
        iP+=25;butProjAcce->move(iP,3);butProjAcce->show();
        iP+=50;butProjBack->move(iP,3);butProjBack->show();
        iP+=34;texJump->setGeometry(iP, 1,26,15);texJump->show();
               labJump->setGeometry(iP,16,26,20);labJump->show();
        iP+=25;butProjJump->move(iP,3);butProjJump->show();
    }
    fRowsStat();
}
void winMain::fMenuClok()
{
    static int iP=0;
    labClok->setText(QTime::currentTime().toString("hh:mm:ss"));
    iP++;
    if (iP==1) fWindLogoFade();
    if (iP==3) fWindLogoHide();
}
void winMain::fMenuClear()
{
    labTime->hide();
    butRoll->hide();
    butProjUpup->hide();
    butProjDown->hide();
    butProjPlay->hide();
    butProjDece->hide();
    labPuls->hide();
    butProjAcce->hide();
    butProjBack->hide();
    labJump->hide();
    butProjJump->hide();
    fMenuAdapt(0);
}

//=================================================================================================
// rows functions
//=================================================================================================

void winMain::fRowsCrea()
{
    gRowsFont.setFamily(qApp->font().family());
    gRowsFont.setPointSize(22);
    gRowsFont.setWeight(50);
    gRowsFont.setItalic(false);
    gRowsBack="#000000";
    gRowsColo="#ffffff";

    objRow0.text="";
    objRow0.show=true;
    objRow0.font.setFamily(qApp->font().family());
    objRow0.font.setPointSize(22);
    objRow0.font.setWeight(50);
    objRow0.font.setItalic(false);
    objRow0.colB=QColor("#000000");
    objRow0.colF=QColor("#ffffff");
    objRow0.colO=gOutlColo;
    objRow0.widt=objWind.widt-2;
    objRow0.heig=objRowsHeig.val0;
    objRow0.spac=objRowsSpac.val0;
    objRow0.rota=objRowsRota.val0;
    objRow0.outl=objRowsOutl.val0;
    objRow0.savH=objRowsHeig.val0;
    objRow0.savS=objRowsSpac.val0;
    objRow0.hori=0;
    objRow0.vert=0;

    fRowsBase(1,0);
    fRowsBase(2,30);
    fRowsBase(3,60);
    fRowsBase(4,90);

    fraRows=new rowSkin(winWind,objWind.basW,objRow4.y+objRow4.heig);
    fraRows->stackUnder(fraMenu);
    connect(fraRows,SIGNAL(sMoved()),this,SLOT(fRowsStat()));

    texRow1=new QLabel(fraRows);
    texRow1->setGeometry(0,0,objRow1.widt,objRow1.heig);
    texRow1->move(objRow1.x,objRow1.y);

    texRow2=new QLabel(fraRows);
    texRow2->setGeometry(0,0,objRow2.widt,objRow2.heig);
    texRow2->move(objRow2.x,objRow2.y);

    texRow3=new QLabel(fraRows);
    texRow3->setGeometry(0,0,objRow3.widt,objRow3.heig);
    texRow3->move(objRow3.x,objRow3.y);

    texRow4=new QLabel(fraRows);
    texRow4->setGeometry(0,0,objRow4.widt,objRow4.heig);
    texRow4->move(objRow4.x,objRow4.y);

    gRowsHcenPrev=0;
    gRowsVcenPrev=0;

    butRowsCent=new QToolButton(fraRows);
    butRowsCent->setIcon(QPixmap(":/Imag/QSTit_cent.png"));
    butRowsCent->setStyleSheet("border:none;");
    butRowsCent->setContentsMargins(0,0,0,0);
    butRowsCent->setIconSize(QSize(16,16));
    butRowsCent->setAutoRepeat(false);
    butRowsCent->setGeometry(gRowsHcen-7,gRowsVcen-7,16,16);
    butRowsCent->hide();
    connect(butRowsCent,SIGNAL(clicked()),this,SLOT(fRowsLocC()));
}
void winMain::fRowsBase(int iR,int iY)
{
    objRows *objRowx=&objRow1;
    if (iR==2) objRowx=&objRow2;
    if (iR==3) objRowx=&objRow3;
    if (iR==4) objRowx=&objRow4;
    objRowx->text=objRow0.text;
    objRowx->show=objRow0.show;
    objRowx->font=objRow0.font;
    objRowx->colB=objRow0.colB;
    objRowx->colF=objRow0.colF;
    objRowx->colO=objRow0.colO;
    objRowx->widt=objRow0.widt;
    objRowx->heig=objRow0.heig;
    objRowx->spac=0;if (iR<4) objRowx->spac=objRow0.spac;
    objRowx->rota=objRow0.rota;
    objRowx->outl=objRow0.outl;
    objRowx->savH=objRow0.savH;
    objRowx->savS=0;if (iR<4) objRowx->savS=objRow0.savS;
    objRowx->hori=objRow0.hori;
    objRowx->vert=objRow0.vert;
    objRowx->x=0;
    objRowx->y=iY;
}
void winMain::fRowsAdapt()
{
    texRow1->setGeometry(objRow1.x,objRow1.y,objRow1.widt,objRow1.heig);
    objRow2.y=objRow1.y+objRow1.heig+objRow1.spac;
    texRow2->setGeometry(objRow2.x,objRow2.y,objRow2.widt,objRow2.heig);
    objRow3.y=objRow2.y+objRow2.heig+objRow2.spac;
    texRow3->setGeometry(objRow3.x,objRow3.y,objRow3.widt,objRow3.heig);
    objRow4.y=objRow3.y+objRow3.heig+objRow3.spac;
    texRow4->setGeometry(objRow4.x,objRow4.y,objRow4.widt,objRow4.heig);
    fraRows->iH=objRow4.y+objRow4.heig-objRow1.x;
    fRowsFramCent();
    fraRows->iX+=gRowsHcenPrev-gRowsHcen;if (fraRows->iX<1) fraRows->iX=1;
    fraRows->iY+=gRowsVcenPrev-gRowsVcen;if (fraRows->iY<1) fraRows->iY=1;
    butRowsCent->hide();
    gRowsHcenPrev=gRowsHcen;
    gRowsVcenPrev=gRowsVcen;
    fRowsFram();
    fRowsTextForm();
}
void winMain::fRowsFram() {fraRows->setGeometry(fraRows->iX,fraRows->iY,fraRows->iW,fraRows->iH);fRowsStat();}
void winMain::fRowsStat()
{
    spiRowsDimV->blockSignals(true);spiRowsDimV->setValue(objRowsHeig.valu);spiRowsDimV->blockSignals(false);
    spiRowsDimH->blockSignals(true);spiRowsDimH->setValue(fraRows->iW);spiRowsDimH->blockSignals(false);
    spiRowsSpac->blockSignals(true);spiRowsSpac->setValue(objRowsSpac.valu);spiRowsSpac->blockSignals(false);
    spiRowsRota->blockSignals(true);spiRowsRota->setValue(objRowsRota.valu);spiRowsRota->blockSignals(false);
    spiRowsOutl->blockSignals(true);spiRowsOutl->setValue(objRowsOutl.valu);spiRowsOutl->blockSignals(false);

    spiShedHei0->blockSignals(true);spiShedHei0->setValue(objRowsHeig.valu);spiShedHei0->blockSignals(false);
    spiShedSpa0->blockSignals(true);spiShedSpa0->setValue(objRowsSpac.valu);spiShedSpa0->blockSignals(false);
    spiShedRot0->blockSignals(true);spiShedRot0->setValue(objRowsRota.valu);spiShedRot0->blockSignals(false);
    spiShedOut0->blockSignals(true);spiShedOut0->setValue(objRowsOutl.valu);spiShedOut0->blockSignals(false);

    spiShedHei1->blockSignals(true);spiShedHei1->setValue(objRow1.heig);spiShedHei1->blockSignals(false);
    spiShedHei2->blockSignals(true);spiShedHei2->setValue(objRow2.heig);spiShedHei2->blockSignals(false);
    spiShedHei3->blockSignals(true);spiShedHei3->setValue(objRow3.heig);spiShedHei3->blockSignals(false);
    spiShedHei4->blockSignals(true);spiShedHei4->setValue(objRow4.heig);spiShedHei4->blockSignals(false);

    spiShedSpa1->blockSignals(true);spiShedSpa1->setValue(objRow1.spac);spiShedSpa1->blockSignals(false);
    spiShedSpa2->blockSignals(true);spiShedSpa2->setValue(objRow2.spac);spiShedSpa2->blockSignals(false);
    spiShedSpa3->blockSignals(true);spiShedSpa3->setValue(objRow3.spac);spiShedSpa3->blockSignals(false);

    spiShedRot1->blockSignals(true);spiShedRot1->setValue(objRow1.rota);spiShedRot1->blockSignals(false);
    spiShedRot2->blockSignals(true);spiShedRot2->setValue(objRow2.rota);spiShedRot2->blockSignals(false);
    spiShedRot3->blockSignals(true);spiShedRot3->setValue(objRow3.rota);spiShedRot3->blockSignals(false);
    spiShedRot4->blockSignals(true);spiShedRot4->setValue(objRow4.rota);spiShedRot4->blockSignals(false);

    spiShedOut1->blockSignals(true);spiShedOut1->setValue(objRow1.outl);spiShedOut1->blockSignals(false);
    spiShedOut2->blockSignals(true);spiShedOut2->setValue(objRow2.outl);spiShedOut2->blockSignals(false);
    spiShedOut3->blockSignals(true);spiShedOut3->setValue(objRow3.outl);spiShedOut3->blockSignals(false);
    spiShedOut4->blockSignals(true);spiShedOut4->setValue(objRow4.outl);spiShedOut4->blockSignals(false);

    labRowsLoca->setText(QString("Rows location = %1,%2").arg(fraRows->iX).arg(fraRows->iY));
    labRowsSize->setText(QString("Rows size = %1,%2").arg(fraRows->iW).arg(fraRows->iH));
    labRowsCent->setText(QString("Rows center = %1,%2").arg(fraRows->iX+gRowsHcen).arg(fraRows->iY+gRowsVcen));
    labMenuSize->setText(QString("Menu location = %1,%2").arg(fraMenu->frameGeometry().x()).arg(fraMenu->frameGeometry().y()));
    labMenuLoca->setText(QString("Menu size = %1,%2").arg(fraMenu->frameGeometry().width()).arg(fraMenu->frameGeometry().height()));
    labScreSize->setText(QString("Screen size = %1,%2").arg(objWind.widt).arg(objWind.heig));
    labGridSize->setText(QString("Grid location = %1,%2").arg(diaGrid->frameGeometry().x()).arg(diaGrid->frameGeometry().y()));
    labGridCol3->setText(QString("Grid c-1 width = %1").arg(griText->columnWidth(3)));
    labGridCol4->setText(QString("Grid c-2 width = %1").arg(griText->columnWidth(4)));
    labGridCol5->setText(QString("Grid c-3 width = %1").arg(griText->columnWidth(5)));
    labGridCol6->setText(QString("Grid c-4 width = %1").arg(griText->columnWidth(6)));
}
void winMain::fRowsFramHeig() {fraRows->iH=objRow4.y+objRow4.heig-objRow1.x;fRowsFramPosi();}
void winMain::fRowsChck()
{
    radShedSho1->setChecked(false);
    radShedSho2->setChecked(false);
    radShedSho3->setChecked(false);
    radShedSho4->setChecked(false);
    if (objRowsNumb.valu>=1) radShedSho1->setChecked(true);
    if (objRowsNumb.valu>=2) radShedSho2->setChecked(true);
    if (objRowsNumb.valu>=3) radShedSho3->setChecked(true);
    if (objRowsNumb.valu==4) radShedSho4->setChecked(true);
}
void winMain::fRowsInit()
{
    butRowsCent->hide();
    if (!gSettShow && !gGridShow)
    {
        fRowsClear();
        fRowsFram();
        fRowsTextForm();
        fRowsShow(1);
    }
    if (gSettShow && !gGridShow)
    {
        QString s1=fL("fRowsInit")+" 1 - "+fL("fRowsInit")+" 1";
        QString s2=fL("fRowsInit")+" 2 - "+fL("fRowsInit")+" 2";
        QString s3=fL("fRowsInit")+" 3 - "+fL("fRowsInit")+" 3";
        QString s4=fL("fRowsInit")+" 4 - "+fL("fRowsInit")+" 4";

        if (gSecoText) s2=fL("fRowsInit")+" 2 / "+fL("fRowsInit")+" 1";
        if (gSecoItal) s2="<i>"+s2+"</i>";

        objRow1.text=s1;
        objRow2.text=s2;
        objRow3.text=s3;
        objRow4.text=s4;

        fRowsFram();
        fRowsTextForm();
        fRowsShow(1);
    }
}
void winMain::fRowsFramCent() {gRowsHcen=fraRows->iW/2;gRowsVcen=fraRows->iH/2;}
void winMain::fRowsFramInit() {if (gWork) {fraRows->iW=gFileMaxiLeng[0];};fRowsFramHeig();}
void winMain::fRowsFramPosi()
{
    fRowsFramCent();
    fraRows->iX+=gRowsHcenPrev-gRowsHcen;if (fraRows->iX<1) fraRows->iX=1;
    fraRows->iY+=gRowsVcenPrev-gRowsVcen;if (fraRows->iY<1) fraRows->iY=1;
    gRowsHcenPrev=gRowsHcen;
    gRowsVcenPrev=gRowsVcen;
    butRowsCent->hide();
    fRowsFram();
}
void winMain::fRowsLocU() {if (fraRows->iY>1) {fraRows->iY--;fRowsFram();}}
void winMain::fRowsLocUFast() {if (fraRows->iY>1) {fraRows->iY-=5;if (fraRows->iY<1) {fraRows->iY=1;};fRowsFram();}}
void winMain::fRowsLocL() {if (fraRows->iX>1) {fraRows->iX--;fRowsFram();}}
void winMain::fRowsLocLFast() {if (fraRows->iX>1) {fraRows->iX-=5;if (fraRows->iX<1) {fraRows->iX=1;};fRowsFram();}}
void winMain::fRowsLocC()
{
    fRowsFramCent();
    butRowsCent->setGeometry(gRowsHcen-8,gRowsVcen-8,16,16);
    if (butRowsCent->isHidden()) butRowsCent->show();
    else butRowsCent->hide();
}
void winMain::fRowsLocR() {if (fraRows->iX+fraRows->iW<objWind.widt-1) {fraRows->iX++;fRowsFram();}}
void winMain::fRowsLocRFast()
{
    if (fraRows->iX+fraRows->iW<objWind.widt-1)
    {
        fraRows->iX+=5;
        if (fraRows->iX+fraRows->iW>objWind.widt-1) fraRows->iX=objWind.widt-fraRows->iW-1;
        fRowsFram();
    }
}
void winMain::fRowsLocD() {if (fraRows->iY<objWind.heig-fraRows->iH-1) {fraRows->iY++;fRowsFram();}}
void winMain::fRowsLocDFast()
{
    if (fraRows->iY<objWind.heig-fraRows->iH-1)
    {
        fraRows->iY+=5;
        if (fraRows->iY>objWind.heig-fraRows->iH-1) fraRows->iY=objWind.heig-fraRows->iH-1;
        fRowsFram();
    }
}
void winMain::fRowsDimH(int pH)
{
    fraRows->iW=pH;
    objRow1.widt=objRow2.widt=objRow3.widt=objRow4.widt=pH;
    fRowsAdapt();
}
void winMain::fRowsDimV(int pV)
{
    objRow1.heig=objRow2.heig=objRow3.heig=objRow4.heig=pV;
    objRow1.savH=objRow2.savH=objRow3.savH=objRow4.savH=pV;
    objRowsHeig.valu=pV;
    fRowsAdapt();
}
void winMain::fShedHeig(int)
{
    objRow1.heig=spiShedHei1->value();
    objRow2.heig=spiShedHei2->value();
    objRow3.heig=spiShedHei3->value();
    objRow4.heig=spiShedHei4->value();
    fRowsAdapt();
}
void winMain::fRowsSpac(int pS)
{
    if (objRow1.show) {objRow1.spac=objRow1.savS=pS;spiShedSpa1->setValue(pS);}
    if (objRow2.show) {objRow2.spac=objRow2.savS=pS;spiShedSpa2->setValue(pS);}
    if (objRow3.show) {objRow3.spac=objRow3.savS=pS;spiShedSpa3->setValue(pS);}
    objRowsSpac.valu=pS;
    fRowsAdapt();
}
void winMain::fShedSpac(int)
{
    objRow1.spac=spiShedSpa1->value();
    objRow2.spac=spiShedSpa2->value();
    objRow3.spac=spiShedSpa3->value();
    fRowsAdapt();
}
void winMain::fRowsRota(int pR)
{
    objRow1.rota=objRow2.rota=objRow3.rota=objRow4.rota=pR;
    objRowsRota.valu=pR;
    fRowsAdapt();
}
void winMain::fShedRota(int)
{
    objRow1.rota=spiShedRot1->value();
    objRow2.rota=spiShedRot2->value();
    objRow3.rota=spiShedRot3->value();
    objRow4.rota=spiShedRot4->value();
    fRowsAdapt();
}
void winMain::fRowsTextForm() {fRowsTextDraw(1);fRowsTextDraw(2);fRowsTextDraw(3);fRowsTextDraw(4);}
void winMain::fRowsTextDraw(int iR)
{
    objRows *objRowx=&objRow1;
    QLabel  *texRowx=texRow1;

    switch (iR)
    {
        case 1: {texRowx=texRow1;objRowx=&objRow1;break;}
        case 2: {texRowx=texRow2;objRowx=&objRow2;break;}
        case 3: {texRowx=texRow3;objRowx=&objRow3;break;}
        case 4: {texRowx=texRow4;objRowx=&objRow4;}
    }
    QString sStyl=QString("<body bgcolor=transparent><style>p{");
    sStyl+=QString("color:%1;").arg(objRowx->colF.name());
    sStyl+=QString("font-family:%1;").arg(objRowx->font.family());
    sStyl+=QString("font-size:%1px;").arg(objRowx->font.pointSize());
    if (objRowx->font.bold()) sStyl+=QString("font-weight:bold;");
    if (objRowx->font.italic()) sStyl+=QString("font-style:italic;");
    if (objRowx->font.underline()) sStyl+=QString("text-decoration:underline;");
    sStyl+=QString("}</style>");

    if (objRowx->hori<0) sStyl+=QString("<p align=left>");
    if (objRowx->hori==0) sStyl+=QString("<p align=center>");
    if (objRowx->hori>0) sStyl+=QString("<p align=right>");

    QPixmap pixRows(texRowx->width(),texRowx->height());
    pixRows.fill(objRowx->colB);

    QPainter painter(&pixRows);

    QTextDocument doc;
    doc.setDocumentMargin(0);
    doc.setPageSize(QSizeF((qreal)texRowx->width(),(qreal)texRowx->height()));
    doc.setTextWidth((qreal)texRowx->width());
    doc.setHtml(sStyl+objRowx->text+"</p>");

    if (objRowx->vert>0) painter.translate(0,0);
    if (objRowx->vert==0) painter.translate(0,(texRowx->height()/2)-(doc.size().height()/2));
    if (objRowx->vert<0) painter.translate(0,(texRowx->height())-(doc.size().height()));

    if (objRowx->rota!=0)
    {
        qreal rRota=((qreal)objRowx->rota/10);
        painter.translate(texRowx->width()/2,texRowx->height()/2);
        painter.rotate(rRota);
        painter.translate(-texRowx->width()/2,-texRowx->height()/2);
    }

    if (objRowx->outl!=0)
    {
        QTextDocument doc2;
        doc2.setDocumentMargin(0);
        doc2.setPageSize(QSizeF((qreal)texRowx->width(),(qreal)texRowx->height()));
        doc2.setTextWidth((qreal)texRowx->width());
        doc2.setHtml(sStyl+objRowx->text+"</p>");

        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(objRowx->colO);
        pen.setWidth(objRowx->outl);

        QTextCharFormat format;
        format.setTextOutline(pen);

        QTextCursor cursor(&doc2);
        cursor.select(QTextCursor::Document);
        cursor.mergeCharFormat(format);

        QRect rec2=QRect(0,0,texRowx->width(),texRowx->height());
        doc2.drawContents(&painter,rec2);
    }
    QRect rect=QRect(0,0,texRowx->width(),texRowx->height());
    doc.drawContents(&painter,rect);
    texRowx->setPixmap(pixRows);

    painter.end();
}
void winMain::fRowsOutl() {gShed=0;fRowsOutlDial();}
void winMain::fRowsOut1() {gShed=1;fRowsOutlDial();}
void winMain::fRowsOut2() {gShed=2;fRowsOutlDial();}
void winMain::fRowsOut3() {gShed=3;fRowsOutlDial();}
void winMain::fRowsOut4() {gShed=4;fRowsOutlDial();}
void winMain::fRowsOutlDial()
{
    if (gOutlDial) {diaColo->close();gOutlDial=false;return;}
    gOutlDial=true;
    QString sC=gOutlColo.name();
    if (gShed==1) sC=objRow1.colO.name();
    if (gShed==2) sC=objRow2.colO.name();
    if (gShed==3) sC=objRow3.colO.name();
    if (gShed==4) sC=objRow4.colO.name();
    diaColo=new diaColoSkin(winWind,fraMenu,fL("diaColoOutl"),sC);
    connect(diaColo,SIGNAL(sClosed()),this,SLOT(fOutlDialClos()));
    connect(diaColo,SIGNAL(sColorGet(QColor)),this,SLOT(fRowsOutlGet(QColor)));
}
void winMain::fOutlDialClos() {gOutlDial=false;}
void winMain::fRowsOutlGet(QColor cColo)
{
    gOutlDial=false;
    gOutlColo=cColo;
    if (gShed==0 || gShed==1) objRow1.colO=cColo;
    if (gShed==0 || gShed==2) objRow2.colO=cColo;
    if (gShed==0 || gShed==3) objRow3.colO=cColo;
    if (gShed==0 || gShed==4) objRow4.colO=cColo;
    fRowsTextForm();
}
void winMain::fRowsOutlThik(int pO)
{
    objRow1.outl=objRow2.outl=objRow3.outl=objRow4.outl=pO;
    spiShedOut1->setValue(pO);spiShedOut2->setValue(pO);spiShedOut3->setValue(pO);spiShedOut4->setValue(pO);
    objRowsOutl.valu=pO;
    fRowsAdapt();
}
void winMain::fShedOutl(int)
{
    objRow1.outl=spiShedOut1->value();
    objRow2.outl=spiShedOut2->value();
    objRow3.outl=spiShedOut3->value();
    objRow4.outl=spiShedOut4->value();
    fRowsAdapt();
}
void winMain::fRowsSeco(int iChck)
{
    gSecoText=iChck ? true:false;
    if (gWork) fGridRows(griText->currentRow());
    else fRowsInit();
}
void winMain::fRowsItal(int iChck)
{
    gSecoItal=iChck ? true:false;
    if (gWork) fGridRows(griText->currentRow());
    else fRowsInit();
}
void winMain::fRowsColo() {gShed=0;fRowsColoDial();}
void winMain::fRowsCol1() {gShed=1;fRowsColoDial();}
void winMain::fRowsCol2() {gShed=2;fRowsColoDial();}
void winMain::fRowsCol3() {gShed=3;fRowsColoDial();}
void winMain::fRowsCol4() {gShed=4;fRowsColoDial();}
void winMain::fRowsColoDial()
{
    if (gColoDial) {diaColo->close();gColoDial=false;return;}
    gColoDial=true;
    QString sC=gRowsColo;
    if (gShed==1) sC=objRow1.colF.name();
    if (gShed==2) sC=objRow2.colF.name();
    if (gShed==3) sC=objRow3.colF.name();
    if (gShed==4) sC=objRow4.colF.name();
    diaColo=new diaColoSkin(winWind,fraMenu,fL("diaTextColo"),sC);
    connect(diaColo,SIGNAL(sClosed()),this,SLOT(fColoDialClos()));
    connect(diaColo,SIGNAL(sColorGet(QColor)),this,SLOT(fRowsColoGet(QColor)));
}
void winMain::fColoDialClos() {gColoDial=false;}
void winMain::fRowsColoGet(QColor cColo)
{
    gColoDial=false;
    if (gShed==0 || gShed==1) objRow1.colF=cColo;
    if (gShed==0 || gShed==2) objRow2.colF=cColo;
    if (gShed==0 || gShed==3) objRow3.colF=cColo;
    if (gShed==0 || gShed==4) objRow4.colF=cColo;
    gRowsColo=cColo.name();
    fRowsTextForm();
    gColoDial=false;
}
void winMain::fRowsBack() {gShed=0;fRowsBackDial();}
void winMain::fRowsBac1() {gShed=1;fRowsBackDial();}
void winMain::fRowsBac2() {gShed=2;fRowsBackDial();}
void winMain::fRowsBac3() {gShed=3;fRowsBackDial();}
void winMain::fRowsBac4() {gShed=4;fRowsBackDial();}
void winMain::fRowsBackDial()
{
    if (gBackDial) {diaColo->close();gBackDial=false;return;}
    gBackDial=true;
    QString sC=gRowsBack;
    if (gShed==1) sC=objRow1.colB.name();
    if (gShed==2) sC=objRow2.colB.name();
    if (gShed==3) sC=objRow3.colB.name();
    if (gShed==4) sC=objRow4.colB.name();
    diaColo=new diaColoSkin(winWind,fraMenu,fL("diaRowsBack"),sC);
    connect(diaColo,SIGNAL(sClosed()),this,SLOT(fBackDialClos()));
    connect(diaColo,SIGNAL(sColorGet(QColor)),this,SLOT(fRowsBackGet(QColor)));
}
void winMain::fBackDialClos() {gBackDial=false;}
void winMain::fRowsBackGet(QColor cColo)
{
    gBackDial=false;
    if (gShed==0 || gShed==1) objRow1.colB=cColo;
    if (gShed==0 || gShed==2) objRow2.colB=cColo;
    if (gShed==0 || gShed==3) objRow3.colB=cColo;
    if (gShed==0 || gShed==4) objRow4.colB=cColo;
    gRowsBack=cColo.name();
    fRowsTextForm();
}
void winMain::fRowsClear() {objRow1.text="";objRow2.text="";objRow3.text="";objRow4.text="";fRowsTextForm();}
void winMain::fRowsHoriLef0() {gShed=0;fRowsHoriLeft();}
void winMain::fRowsHoriLef1() {gShed=1;fRowsHoriLeft();}
void winMain::fRowsHoriLef2() {gShed=2;fRowsHoriLeft();}
void winMain::fRowsHoriLef3() {gShed=3;fRowsHoriLeft();}
void winMain::fRowsHoriLef4() {gShed=4;fRowsHoriLeft();}
void winMain::fRowsHoriLeft()
{
    if (gShed==0 || gShed==1) objRow1.hori=-1;
    if (gShed==0 || gShed==2) objRow2.hori=-1;
    if (gShed==0 || gShed==3) objRow3.hori=-1;
    if (gShed==0 || gShed==4) objRow4.hori=-1;
    fRowsTextForm();
}
void winMain::fRowsHoriCen0() {gShed=0;fRowsHoriCent();}
void winMain::fRowsHoriCen1() {gShed=1;fRowsHoriCent();}
void winMain::fRowsHoriCen2() {gShed=2;fRowsHoriCent();}
void winMain::fRowsHoriCen3() {gShed=3;fRowsHoriCent();}
void winMain::fRowsHoriCen4() {gShed=4;fRowsHoriCent();}
void winMain::fRowsHoriCent()
{
    if (gShed==0 || gShed==1) objRow1.hori=0;
    if (gShed==0 || gShed==2) objRow2.hori=0;
    if (gShed==0 || gShed==3) objRow3.hori=0;
    if (gShed==0 || gShed==4) objRow4.hori=0;
    fRowsTextForm();
}
void winMain::fRowsHoriRig0() {gShed=0;fRowsHoriRigh();}
void winMain::fRowsHoriRig1() {gShed=1;fRowsHoriRigh();}
void winMain::fRowsHoriRig2() {gShed=2;fRowsHoriRigh();}
void winMain::fRowsHoriRig3() {gShed=3;fRowsHoriRigh();}
void winMain::fRowsHoriRig4() {gShed=4;fRowsHoriRigh();}
void winMain::fRowsHoriRigh()
{
    if (gShed==0 || gShed==1) objRow1.hori=1;
    if (gShed==0 || gShed==2) objRow2.hori=1;
    if (gShed==0 || gShed==3) objRow3.hori=1;
    if (gShed==0 || gShed==4) objRow4.hori=1;
    fRowsTextForm();
}
void winMain::fRowsVertBot0() {gShed=0;fRowsVertBott();}
void winMain::fRowsVertBot1() {gShed=1;fRowsVertBott();}
void winMain::fRowsVertBot2() {gShed=2;fRowsVertBott();}
void winMain::fRowsVertBot3() {gShed=3;fRowsVertBott();}
void winMain::fRowsVertBot4() {gShed=4;fRowsVertBott();}
void winMain::fRowsVertBott()
{
    if (gShed==0 || gShed==1) objRow1.vert=-1;
    if (gShed==0 || gShed==2) objRow2.vert=-1;
    if (gShed==0 || gShed==3) objRow3.vert=-1;
    if (gShed==0 || gShed==4) objRow4.vert=-1;
    fRowsTextForm();
}
void winMain::fRowsVertCen0() {gShed=0;fRowsVertCent();}
void winMain::fRowsVertCen1() {gShed=1;fRowsVertCent();}
void winMain::fRowsVertCen2() {gShed=2;fRowsVertCent();}
void winMain::fRowsVertCen3() {gShed=3;fRowsVertCent();}
void winMain::fRowsVertCen4() {gShed=4;fRowsVertCent();}
void winMain::fRowsVertCent()
{
    if (gShed==0 || gShed==1) objRow1.vert=0;
    if (gShed==0 || gShed==2) objRow2.vert=0;
    if (gShed==0 || gShed==3) objRow3.vert=0;
    if (gShed==0 || gShed==4) objRow4.vert=0;
    fRowsTextForm();
}
void winMain::fRowsVertTop0() {gShed=0;fRowsVertTopy();}
void winMain::fRowsVertTop1() {gShed=1;fRowsVertTopy();}
void winMain::fRowsVertTop2() {gShed=2;fRowsVertTopy();}
void winMain::fRowsVertTop3() {gShed=3;fRowsVertTopy();}
void winMain::fRowsVertTop4() {gShed=4;fRowsVertTopy();}
void winMain::fRowsVertTopy()
{
    if (gShed==0 || gShed==1) objRow1.vert=1;
    if (gShed==0 || gShed==2) objRow2.vert=1;
    if (gShed==0 || gShed==3) objRow3.vert=1;
    if (gShed==0 || gShed==4) objRow4.vert=1;
    fRowsTextForm();
}
void winMain::fRowsNumb()
{
    objRow1.show=false;objRow2.show=false;objRow3.show=false;objRow4.show=false;
    if (objRowsNumb.valu>=1) objRow1.show=true;
    if (objRowsNumb.valu>=2) objRow2.show=true;
    if (objRowsNumb.valu>=3) objRow3.show=true;
    if (objRowsNumb.valu==4) objRow4.show=true;
    fRowsNumbAdap();
    if (gGridShow) fGridInit();
}
void winMain::fShedNumb()
{
    objRow1.show=radShedSho1->isChecked();
    objRow2.show=radShedSho2->isChecked();
    objRow3.show=radShedSho3->isChecked();
    objRow4.show=radShedSho4->isChecked();
    fRowsNumbAdap();
    if (gGridShow) fGridInit();
}
void winMain::fRowsNumbAdap()
{
    radShedSho1->blockSignals(true);radShedSho1->setChecked(objRow1.show);radShedSho1->blockSignals(false);
    texRow1->setHidden(!objRow1.show);
    if (objRow1.show) {objRowsNumb.valu=1;objRow1.heig=objRow1.savH;objRow1.spac=objRow1.savS;}
    else
    {
        if (objRow1.heig!=0) {objRow1.savH=objRow1.heig;objRow1.savS=objRow1.spac;}
        objRow1.heig=0;objRow1.spac=0;
    }
    spiShedHei1->blockSignals(true);spiShedHei1->setValue(objRow1.heig);spiShedHei1->blockSignals(false);
    spiShedSpa1->blockSignals(true);spiShedSpa1->setValue(objRow1.spac);spiShedSpa1->blockSignals(false);

    radShedSho2->blockSignals(true);radShedSho2->setChecked(objRow2.show);radShedSho2->blockSignals(false);
    texRow2->setHidden(!objRow2.show);
    if (objRow2.show) {objRowsNumb.valu=2;objRow2.heig=objRow2.savH;objRow2.spac=objRow2.savS;}
    else
    {
        if (objRow2.heig!=0) {objRow2.savH=objRow2.heig;objRow2.savS=objRow2.spac;}
        objRow2.heig=0;objRow2.spac=0;
    }
    spiShedHei2->blockSignals(true);spiShedHei2->setValue(objRow2.heig);spiShedHei2->blockSignals(false);
    spiShedSpa2->blockSignals(true);spiShedSpa2->setValue(objRow2.spac);spiShedSpa2->blockSignals(false);

    radShedSho3->blockSignals(true);radShedSho3->setChecked(objRow3.show);radShedSho3->blockSignals(false);
    texRow3->setHidden(!objRow3.show);
    if (objRow3.show) {objRowsNumb.valu=3;objRow3.heig=objRow3.savH;objRow3.spac=objRow3.savS;}
    else
    {
        if (objRow3.heig!=0) {objRow3.savH=objRow3.heig;objRow3.savS=objRow3.spac;}
        objRow3.heig=0;objRow3.spac=0;
    }
    spiShedHei3->blockSignals(true);spiShedHei3->setValue(objRow3.heig);spiShedHei3->blockSignals(false);
    spiShedSpa3->blockSignals(true);spiShedSpa3->setValue(objRow3.spac);spiShedSpa3->blockSignals(false);

    radShedSho4->blockSignals(true);radShedSho4->setChecked(objRow4.show);radShedSho4->blockSignals(false);
    texRow4->setHidden(!objRow4.show);
    if (objRow4.show) {objRowsNumb.valu=4;objRow4.heig=objRow4.savH;}
    else
    {
        if (objRow4.heig!=0) {objRow4.savH=objRow4.heig;}
        objRow4.heig=0;
    }
    spiShedHei4->blockSignals(true);spiShedHei4->setValue(objRow4.heig);spiShedHei4->blockSignals(false);

    fRowsAdapt();
}
void winMain::fRowsFont() {gShed=0;fRowsFontDial();}
void winMain::fRowsFon1() {gShed=1;fRowsFontDial();}
void winMain::fRowsFon2() {gShed=2;fRowsFontDial();}
void winMain::fRowsFon3() {gShed=3;fRowsFontDial();}
void winMain::fRowsFon4() {gShed=4;fRowsFontDial();}
void winMain::fRowsFontDial()
{
    if (gFontDial) {diaFont->close();gFontDial=false;return;}
    gFontDial=true;
    QFont fF=gRowsFont;
    if (gShed==1) fF=objRow1.font;
    if (gShed==2) fF=objRow2.font;
    if (gShed==3) fF=objRow3.font;
    if (gShed==4) fF=objRow4.font;
    diaFont=new diaFontSkin(winWind,fraMenu,fL("diaTextFont"),fF);
    connect(diaFont,SIGNAL(sClosed()),this,SLOT(fFontDialClos()));
    connect(diaFont,SIGNAL(sFontGet(QFont)),this,SLOT(fRowsFontGet(QFont)));
}
void winMain::fFontDialClos() {gFontDial=false;}
void winMain::fRowsFontGet(QFont pFont)
{
    if (pFont.pointSize()<8) pFont.setPointSize(8);
    if (gShed==0 || gShed==1) objRow1.font=pFont;
    if (gShed==0 || gShed==2) objRow2.font=pFont;
    if (gShed==0 || gShed==3) objRow3.font=pFont;
    if (gShed==0 || gShed==4) objRow4.font=pFont;
    gRowsFont=pFont;
    fRowsFontChan();
    gFontDial=false;
}
void winMain::fRowsFontChan() {fRowsHeigCalc();fRowsWidtCalc();fRowsAdapt();}
void winMain::fRowsHeigCalc()
{
    int iHone=(gRowsFont.pointSize()*2)/1.3;
    if (iHone>objRowsHeig.maxi) iHone=objRowsHeig.maxi;
    if (gShed==0 || gShed==1) objRow1.heig=iHone;
    if (gShed==0 || gShed==2) objRow2.heig=iHone;
    if (gShed==0 || gShed==3) objRow3.heig=iHone;
    if (gShed==0 || gShed==4) objRow4.heig=iHone;
    objRowsHeig.valu=iHone;
}
void winMain::fRowsWidtCalc()
{
    if (!gWork) {fraRows->iW=objWind.widt-fraRows->iX-1;}
    else
    {
        int iM,iW;
        QString sT;
        QFont fT=gRowsFont;
        if (fT.pointSize()<objRow1.font.pointSize()) fT=objRow1.font;
        if (fT.pointSize()<objRow2.font.pointSize()) fT=objRow2.font;
        if (fT.pointSize()<objRow3.font.pointSize()) fT=objRow3.font;
        if (fT.pointSize()<objRow4.font.pointSize()) fT=objRow4.font;
        QFontMetrics mRows=QFontMetrics(fT);
        for (iM=0; iM<9; iM++)
        {
            sT=griText->item(gFileMaxiRows[iM],gFileMaxiColo[iM])->text().trimmed();
            gFileMaxiLeng[iM]=mRows.width(sT);
        }
        iW=gFileMaxiLeng[0]/1.3;
        if (iW%2!=0) iW+=1;
        if (iW<objRowsWidt.mini) {iW=objRowsWidt.mini;}
        if (iW>objWind.basW) {iW=objWind.basW;messSkin cM;cM.fMess(this,fraMenu,fL("msgFontWideMess"),fL("butOkOk"),"");}
        fraRows->iW=iW;
    }
    objRow1.widt=fraRows->iW;
    objRow2.widt=fraRows->iW;
    objRow3.widt=fraRows->iW;
    objRow4.widt=fraRows->iW;
}
void winMain::fRowsShowSlot() {fRowsShow(-1);}
void winMain::fRowsShow(int pShow)
{
    static int sShow=1;

    if (pShow!=-1) sShow=pShow;
    else sShow=sShow==0 ? 1:0;
    if (sShow==1)   {fraRows->show();butRoll->setIcon(QPixmap(":/Imag/QSTit_roll_open.png"));}
    else            {fraRows->hide();butRoll->setIcon(QPixmap(":/Imag/QSTit_roll_clos.png"));}
}

//=================================================================================================
// grid functions
//=================================================================================================

void winMain::fGridCrea()
{
    gGridModi=gGridMark=0;
    gGridRowsHeig=18;
    int gGridWidt=objWind.widt-2;
    int gGridHeig=34+(7*gGridRowsHeig);

    diaGrid=new diaGridSkin(winWind,fraMenu,fL("Grid"),gGridWidt,gGridHeig);
    diaGrid->fWorkLang(gLangCode,gLangText);
    connect(diaGrid,SIGNAL(sMoved()),this,SLOT(fRowsStat()));

    griText=new diaGridC(diaGrid,winWind,fraMenu);
    griText->stackUnder(diaGrid->fraSizL);
    griText->setColumnCount(7);
    griText->setGeometry(2,31,gGridWidt-81,2+(7*gGridRowsHeig));
    griText->setSelectionBehavior(QAbstractItemView::SelectRows);
    griText->setSelectionMode(QAbstractItemView::SingleSelection);
    griText->setStyleSheet(gGriCStyl);
    connect(griText,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(fGridChan(int,int,int,int)));
    connect(griText,SIGNAL(cellClicked(int,int)),this,SLOT(fGridClic(int,int)));
    griText->fWorkLang(gLangCode,gLangText);

    butGridInfo=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_info_enab.png"),"M"+fL("butGridInfo"),false);
    butGridInfo->move(gGridWidt-69,36);
    connect(butGridInfo,SIGNAL(clicked()),this,SLOT(fFileInfoDial()));

    butGridSave=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_save_disa.png"),"M"+fL("butGridSave"),false);
    butGridSave->move(gGridWidt-39,36);
    connect(butGridSave,SIGNAL(clicked()),this,SLOT(fGridSave()));

    butGridEdit=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_edit_enab.png"),"M"+fL("butGridEdit"),false);
    butGridEdit->move(gGridWidt-69,66);
    connect(butGridEdit,SIGNAL(clicked()),this,SLOT(fGridEditButt()));

    butGridUndo=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_undo_disa.png"),"M"+fL("butGridUndo"),false);
    butGridUndo->move(gGridWidt-39,66);
    connect(butGridUndo,SIGNAL(clicked()),this,SLOT(fGridUndo()));

    butGridGoto=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_goto_enab.png"),"M"+fL("butGridGoto"),false);
    butGridGoto->move(gGridWidt-69,96);
    connect(butGridGoto,SIGNAL(clicked()),this,SLOT(fGridGoto()));

    butGridFind=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_find_enab.png"),"M"+fL("butGridFind"),false);
    butGridFind->move(gGridWidt-39,96);
    connect(butGridFind,SIGNAL(clicked()),this,SLOT(fGridFind()));

    butGridClea=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_clea.png"),"M"+fL("butGridClea"),false);
    butGridClea->move(gGridWidt-69,126);
    connect(butGridClea,SIGNAL(clicked()),this,SLOT(fClearGrid()));

    butGridLink=new butToolC(diaGrid,QPixmap(":/Imag/QSTit_link_none.png"),"M"+fL("butLink"),false);
    butGridLink->move(gGridWidt-39,126);
    connect(butGridLink,SIGNAL(clicked()),this,SLOT(fGridLink()));
}
void winMain::fGridLink()
{
    diaGrid->fGridLink();
    if (diaGrid->bLink) butGridLink->setIcon(QPixmap(":/Imag/QSTit_link_none.png"));
    else butGridLink->setIcon(QPixmap(":/Imag/QSTit_link_done.png"));
}
void winMain::fGridColo()
{
    QString sSele="selection-background-color:#0055aa;selection-color:#000000;border:none;";

    if (!gGridColoDark) {gGridBack="#222222";gGridColo="#ffffff";gGridColoDark=true;}
    else                {gGridBack="#ffffff";gGridColo="#000000";gGridColoDark=false;}
    radGridDark->setChecked(gGridColoDark);
    gGriCStyl="background:"+gGridBack+";color:"+gGridColo+";"+sSele;
    griText->setStyleSheet(gGriCStyl);
    fWindStyle();
}
void winMain::fGridItemSetx(QString sText,int iR,int iC)
{
    QTableWidgetItem *wi=new QTableWidgetItem(sText,0);
    wi->setFont(gGridFont);
    wi->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    griText->setItem(iR,iC,wi);
}
void winMain::fGridEditEnab()
{
    gGridEdit=true;
    butGridEdit->setIcon(QPixmap(":/Imag/QSTit_edit_enab.png"));
    butGridFind->setIcon(QPixmap(":/Imag/QSTit_find_enab.png"));
    butGridGoto->setIcon(QPixmap(":/Imag/QSTit_goto_enab.png"));
    butGridInfo->setIcon(QPixmap(":/Imag/QSTit_info_enab.png"));
    butHelp->setIcon(QPixmap(":/Imag/QSTit_help_enab.png"));
}
void winMain::fGridEditDisa()
{
    gGridEdit=false;
    butGridEdit->setIcon(QPixmap(":/Imag/QSTit_edit_disa.png"));
    butGridFind->setIcon(QPixmap(":/Imag/QSTit_find_disa.png"));
    butGridGoto->setIcon(QPixmap(":/Imag/QSTit_goto_disa.png"));
    butGridInfo->setIcon(QPixmap(":/Imag/QSTit_info_disa.png"));
    butHelp->setIcon(QPixmap(":/Imag/QSTit_help_disa.png"));
}
void winMain::fGridSaveIcon()
{
    if (diaGrid)
    {
        if (gGridModi>0)
        {
            butGridSave->setIcon(QPixmap(":/Imag/QSTit_save_enab.png"));
            butGridUndo->setIcon(QPixmap(":/Imag/QSTit_undo_enab.png"));
        }
        else
        {
            butGridSave->setIcon(QPixmap(":/Imag/QSTit_save_disa.png"));
            butGridUndo->setIcon(QPixmap(":/Imag/QSTit_undo_disa.png"));
        }
    }
}
void winMain::fGridZero()
{
    int iGrid;
    griText->setRowCount(2);
    griText->setColumnCount(7);
    if (gSrtx)
    {
        iGrid=0;
        fGridItemSetx("",iGrid,0);
        fGridItemSetx("00:00:00,000",iGrid,1);
        fGridItemSetx("00:00:00,000",iGrid,2);
        fGridItemSetx("",iGrid,3);
        fGridItemSetx("",iGrid,4);
        fGridItemSetx("",iGrid,5);
        fGridItemSetx("",iGrid,6);
        iGrid=1;
        fGridItemSetx("",iGrid,0);
        fGridItemSetx("99:99:99,999",iGrid,1);
        fGridItemSetx("99:99:99,999",iGrid,2);
        fGridItemSetx("",iGrid,3);
        fGridItemSetx("",iGrid,4);
        fGridItemSetx("",iGrid,5);
        fGridItemSetx("",iGrid,6);
    }
    else
    {
        iGrid=0;
        fGridItemSetx("",iGrid,0);
        fGridItemSetx("",iGrid,1);
        fGridItemSetx("",iGrid,2);
        fGridItemSetx("",iGrid,3);
        fGridItemSetx("",iGrid,4);
        fGridItemSetx("",iGrid,5);
        fGridItemSetx("",iGrid,6);
        iGrid=1;
        fGridItemSetx("",iGrid,0);
        fGridItemSetx("",iGrid,1);
        fGridItemSetx("",iGrid,2);
        fGridItemSetx("",iGrid,3);
        fGridItemSetx("",iGrid,4);
        fGridItemSetx("",iGrid,5);
        fGridItemSetx("",iGrid,6);
    }
}
void winMain::fGridTitle()
{
    QFileInfo fInfo=QFileInfo(gFile);
    QString sTitl=fInfo.fileName()+"     ( ";
    sTitl+=QString("%1").arg(gRowsMaxi-1) + " " + fL("diaGridTitlLine") + " · ";
    sTitl+=fL("diaGridTitlWidt")+": "+QString("%1").arg(gFileMaxiRows[0]);
    if (gSrtx) sTitl+= " · "+fL("diaGridTitlEnd")+": "+gSrtxStop.left(8);
    sTitl+= " )";
    diaGrid->labTitl->setText(sTitl);
}
void winMain::fGridInit()
{
    for (int iR=0; iR<99; iR++)
    {
        gEditTextRows[iR]=0;
        gEditTextColu[iR]=0;
        gEditTextLine[iR]=0;
        gEditTextOldx[iR]="";
        gEditTextNewx[iR]="";
    }
    griText->horizontalHeader()->setFixedHeight(2);
    griText->verticalHeader()->setFixedWidth(31);
    fGridInitCols();
    fGridInitRows();
}
void winMain::fGridInitCols()
{
    int c,cw;
    int cwTot=142;                              // 30+1 n°ligne,20+1 status,10+1 ascenseur,80+1 boutons
    int cwMax=(objWind.widt-2-cwTot)/objRowsNumb.valu;

    for (c=0; c<7; c++) {griText->setColumnWidth(c,0);}
    griText->setColumnWidth(0,20);
    if (gSrtx)
    {
        QFontMetrics mGrid=QFontMetrics(gGridFont);
        cw=mGrid.width("99:99:99,999")+9;
        griText->setColumnWidth(1,cw);
        griText->setColumnWidth(2,cw);
        cwTot+=cw*2;
        cwMax=(objWind.widt-2-cwTot)/objRowsNumb.valu;
    }
    for (c=3; c<7; c++)
    {
        cw=gFileMaxiColu[c-3];
        if (cw>0) cw+=9;
        if (cw>cwMax) cw=cwMax;
        cwTot+=cw;
        switch (c)
        {
            case 3: diaGrid->iWid3=cw;
            case 4: diaGrid->iWid4=cw;
            case 5: diaGrid->iWid5=cw;
            case 6: diaGrid->iWid6=cw;
        }
    }
    diaGrid->nColo=objRowsNumb.valu;
    diaGrid->fGridSizeInit(cwTot,griText->rowCount());
    fRowsStat();
}
void winMain::fGridInitRows()
{
    for (int iR=0; iR<griText->rowCount(); iR++)
    {
        griText->setRowHeight(iR,gGridRowsHeig);
        griText->setVerticalHeaderItem(iR,new QTableWidgetItem(QString("%1").arg(iR)));
    }
}
void winMain::fGridShow(bool bShow)
{
    if (bShow) {gGridShow=true;diaGrid->fRePosi();diaGrid->show();}
    else {gGridShow=false;diaGrid->hide();}
}
QString winMain::fGridTextClean(QString sText)
{
    QString sT=sText.trimmed();
    sT.remove("<b>");sT.remove("</b>");sT.remove("<i>");sT.remove("</i>");sT.remove("<u>");sT.remove("</u>");
    return sT;
}
void winMain::fGridRows(int r)
{
    QString st1=griText->item(r,3)->text();
    QString st2="";

    if (objRowsNumb.valu>1)
    {
        st2=griText->item(r,4)->text();
        if (gSecoText && st2.isEmpty())
        {
            st2=st1;
            st1="";
        }
        if (gSecoItal)
        {
            if (st2.indexOf("<i>")==-1) {st2="<i>"+st2+"</i>";}
            else {st2.remove("<i>");st2.remove("</i>");}
        }
    }
    objRow1.text=st1;
    if (objRowsNumb.valu>1) objRow2.text=st2;
    if (objRowsNumb.valu>2) objRow3.text=griText->item(r,5)->text();
    if (objRowsNumb.valu>3) objRow4.text=griText->item(r,6)->text();
    fRowsTextForm();
}
void winMain::fGridChan(int iR,int iC,int,int) {griText->setCurrentCell(iR,iC);fGridRows(iR);}
void winMain::fGridClic(int iR,int iC)
{
    if (iC==0) {fGridMarkRows(iR);return;}
    if (gAuto && !gInit) {griText->setCurrentCell(iR,iC);fAutoStarInit();}
    if (gAuto && gInit)
    {
        if (gPlay) tmrAuto->stop();
        griText->setCurrentCell(iR,iC);
        fAutoStarInit();
        if (gPlay) tmrAuto->start();
    }
}

void winMain::fGridEditButt() {fGridEdit(griText->currentRow(),griText->currentColumn());}
void winMain::fGridEdit(int iR,int iC)
{
    if (!gGridEdit || iC==0 || iR==0 || iR==gRowsMaxi)
    {
        messSkin cM;cM.fMess(this,fraMenu,fL("msgGridEditMess"),fL("butOkOk"),"");return;
    }

    int iLineWidt=griText->columnWidth(iC)+10;
    int iLineHeig=20;
    int iWidt=iLineWidt+95;
    int iHeig=65;
    int iLefx=diaGrid->frameGeometry().x()+diaGrid->frameGeometry().width()-iWidt-79;
    int iTopy=diaGrid->frameGeometry().y()+2;

    diaEdit=new QDialog(diaGrid);
    diaEdit->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    diaEdit->setModal(true);
    diaEdit->setCursor(Qt::ArrowCursor);
    diaEdit->setMinimumSize(iWidt,iHeig);
    diaEdit->setMaximumSize(iWidt,iHeig);
    diaEdit->setGeometry(iLefx,iTopy,iWidt,iHeig);
    diaEdit->move(iLefx,iTopy);

    QString sStyl="QDialog {font:normal 11px "+gSystFontFami+";background-color:#32cd32;color:#000000;border:none}";
    sStyl+="QLineEdit {background-color:#ffffff;color:#000000;border:1px solid #202020;font:11px normal courier new;}";
    sStyl+="QLabel {background-color:#32cd32;color:#202020;border:none;text-align:left;}";
    sStyl+="QPushButton {background-color:#202020;color:#ffffff;border:none;text-align:left;padding-left:2px;}";
    diaEdit->setStyleSheet(sStyl);

    QTableWidgetItem *wi=griText->item(iR,iC);

    QLineEdit *ediLine=new QLineEdit(diaEdit);
    ediLine->setFont(gGridFont);
    ediLine->setEchoMode(QLineEdit::Normal);
    ediLine->setText(QString(wi->text()));
    ediLine->setGeometry(10,10,iLineWidt,iLineHeig);
    ediLine->setFocus();
    connect(ediLine,SIGNAL(returnPressed()),this,SLOT(fGridEditSave()));

    butEditSave=new QPushButton(QPixmap(":/Imag/QSTit_okok.png"),fL("butEditSave"),diaEdit);
    butEditSave->setIconSize(QSize(16,16));
    butEditSave->resize(70,20);
    butEditSave->move(iLineWidt+15,10);
    connect(butEditSave,SIGNAL(clicked()),this,SLOT(fGridEditSave()));

    butEditCanc=new QPushButton(QPixmap(":/Imag/QSTit_canc.png"),fL("butEditCanc"),diaEdit);
    butEditCanc->setIconSize(QSize(16,16));
    butEditCanc->resize(70,20);
    butEditCanc->move(iLineWidt+15,35);
    connect(butEditCanc,SIGNAL(clicked()),this,SLOT(fGridEditCanc()));

    gGridEditSave=false;
    QString sTextOrig=wi->text();

    diaEdit->exec();

    if (gGridEditSave && ediLine->isModified())
    {
        gGridSave=true;
        gGridModi++;
        wi->setText(ediLine->text());
        QTableWidgetItem *wic=griText->item(iR,0);
        wic->setIcon(QPixmap(":/Imag/QSTit_edit.png"));
        wic->setText("E");
        fGridSaveIcon();
        fGridRows(iR);
        fGridEditMemo(iR,iC,sTextOrig);
    }

    fGridFocus();
}
void winMain::fGridEditMemo(int iR,int iC,QString sTextOrig)
{
    QTableWidgetItem *wi=griText->item(iR,iC);
    gEditTextRows[gGridModi]=iR;
    gEditTextColu[gGridModi]=iC;
    gEditTextLine[gGridModi]=(iR+1) / 2;
    gEditTextOldx[gGridModi]=sTextOrig;
    gEditTextNewx[gGridModi]=wi->text();
}
void winMain::fGridEditCanc() {gGridEditSave=false;diaEdit->done(0);}
void winMain::fGridEditSave() {gGridEditSave=true;diaEdit->done(0);}
void winMain::fGridModi()
{
    if (gGridSave)
    {
        messSkin cM;if (cM.fMess(this,fraMenu,fL("GridTextModiMess"),fL("butYeYe"),fL("butNoNo"))) fGridSave();
    }
}
void winMain::fGridMarkRows(int iR)
{
    if (iR==0 || iR==gRowsMaxi) return;

    QTableWidgetItem *wi=griText->item(iR,0);

    if (wi->text()=="E") return;

    QIcon ic=wi->icon();

    if (!ic.isNull())
    {
        QTableWidgetItem *wi=new QTableWidgetItem("",0);
        wi->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        griText->setItem(iR,0,wi);
        gGridMark--;
    }
    else
    {
        QTableWidgetItem *wi=griText->item(iR,0);
        wi->setIcon(QPixmap(":/Imag/QSTit_flag.png"));
        wi->setText("I");
        gGridMark++;
    }
}
void winMain::fGridUndo()
{
    if (!gGridEdit || gGridModi==0) return;

    int iR=gEditTextRows[gGridModi];
    int iC=gEditTextColu[gGridModi];

    griText->item(iR,iC)->setText(gEditTextOldx[gGridModi]);

    QTableWidgetItem *ic=new QTableWidgetItem("",0);
    ic->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    griText->setItem(iR,0,ic);

    gGridModi--;
    if (gGridModi==0) gGridSave=false;
    fGridSaveIcon();
}
void winMain::fGridSave()
{
    if (!gGridSave) return;
    if (gAuto && gPlay) return;

    QString sFile=gFile;

    sFile=QFileDialog::getSaveFileName(this,fL("diaSaveFileTitl"),sFile,fL("diaSaveFileExte"));
    if (sFile.isEmpty())
    {
        griText->setFocus();
        return;
    }

    if (gSrtx) fFileWritSrtx(sFile);
    else fFileWrit(sFile);

    fGridSaveIcon();
    griText->setFocus();
}
void winMain::fGridFontDial()
{
    if (gGridDial) {diaFont->close();gGridDial=false;return;}
    gGridDial=true;
    diaFont=new diaFontSkin(winWind,fraMenu,fL("diaGridFont"),gGridFont);
    connect(diaFont,SIGNAL(sClosed()),this,SLOT(fGridFontClos()));
    connect(diaFont,SIGNAL(sFontGet(QFont)),this,SLOT(fGridFontGet(QFont)));
}
void winMain::fGridFontClos() {gGridDial=false;}
void winMain::fGridFontGet(QFont pFont)
{
    if (gGridFont!=pFont) {gGridFont=pFont;fGridFontSize();}
    gGridDial=false;
}
void winMain::fGridFontSize()
{
    if (gGridFont.pointSize()<8) gGridFont.setPointSize(8);
    if (gGridFont.pointSize()>16) gGridFont.setPointSize(16);
    if (gGridFont.pointSize()<=9) gGridRowsHeig=18;
    if (gGridFont.pointSize()==10) gGridRowsHeig=19;
    if (gGridFont.pointSize()>=11) gGridRowsHeig=20;
    if (gWork)
    {
        int iR,iC;
        int iCmax=3+objRowsNumb.valu;
        QTableWidgetItem *wi;
        QFontMetrics mGrid=QFontMetrics(gGridFont);
        QFontMetrics mRows=QFontMetrics(gRowsFont);

        fFileTextMaxi(-1,0,0,0,0,0);
        for (iR=0; iR<=gRowsMaxi; iR++)
        {
            for (iC=1; iC<iCmax; iC++)
            {
                wi=griText->item(iR,iC);
                wi->setFont(gGridFont);
                fFileTextMaxi(mGrid.width(wi->text()),mRows.width(wi->text()),wi->text().length(),iR,iR,iC);
            }
        }
        fGridInitCols();
        fGridInitRows();
    }
}
void winMain::fGridGoto()
{
    if (gAuto && gPlay) return;
    QApplication::sendEvent(griText,new QKeyEvent(QEvent::KeyPress,Qt::Key_G,Qt::ControlModifier,"",false,1));
}
void winMain::fGridFind()
{
    if (gAuto && gPlay) return;
    QApplication::sendEvent(griText,new QKeyEvent(QEvent::KeyPress,Qt::Key_F,Qt::ControlModifier,"",false,1));
}
void winMain::fGridFocus() {diaGrid->activateWindow();griText->setFocus();}
void winMain::fGridColoTogg() {gGridColoDark=!radGridDark->isChecked();fGridColo();}

//=================================================================================================
// settings functions
//=================================================================================================

void winMain::fSettCrea()
{
    gSettShow=false;
    gSettWidt=690;
    gSettHeig=310;
    gSettLefx=gSettTopy=0;

    diaSett=new diaSkin(winWind,fraMenu,fL("diaSett"),gSettWidt,gSettHeig,-1,-1);
    connect(diaSett,SIGNAL(sClosed()),this,SLOT(fSettClos()));

    tabSett=new QTabWidget(diaSett);
    tabSett->setTabPosition(QTabWidget::North);
    tabSett->setGeometry(gSettLefx,gSettTopy,gSettWidt,gSettHeig);
    tabSett->setGeometry(3,32,gSettWidt-4,gSettHeig-34);
    tabSett->setCursor(Qt::ArrowCursor);
    tabSett->setStyleSheet("border:none;");

    // page 1 - texts frame ---------------------------------------------------

    tabRows=new QWidget;
    tabRows->setStyleSheet("border:none;background-color:#151515;");

    texRowsFram=new QLabel(fL("texRowsFram"),tabRows);
    texRowsFram->setMinimumWidth(70);
    texRowsFram->move(10,10);

    texRowsLoca=new QLabel(fL("texRowsLoca"),tabRows);
    texRowsLoca->setMinimumWidth(70);
    texRowsLoca->move(105,10);
    grpSkin *grpRowsLoca=new grpSkin(tabRows,75,70,105,30);
    butLocaUpup=new butToolX(grpRowsLoca);
    butLocaUpup->setText(fL("butLocaUpup"));
    butLocaUpup->setIcon(QPixmap(":/Imag/QSTit_xupx.png"));
    butLocaUpup->move(29,7);
    connect(butLocaUpup,SIGNAL(clicked()),this,SLOT(fRowsLocU()));
    butLocaLeft=new butToolX(grpRowsLoca);
    butLocaLeft->setText(fL("butLocaLeft"));
    butLocaLeft->setIcon(QPixmap(":/Imag/QSTit_xlef.png"));
    butLocaLeft->move(9,27);
    connect(butLocaLeft,SIGNAL(clicked()),this,SLOT(fRowsLocL()));
    butLocaCent=new butToolX(grpRowsLoca);
    butLocaCent->setText(fL("butLocaCent"));
    butLocaCent->setIcon(QPixmap(":/Imag/QSTit_cent.png"));
    butLocaCent->move(29,27);
    connect(butLocaCent,SIGNAL(clicked()),this,SLOT(fRowsLocC()));
    butLocaRigh=new butToolX(grpRowsLoca);
    butLocaRigh->setText(fL("butLocaRigh"));
    butLocaRigh->setIcon(QPixmap(":/Imag/QSTit_xrig.png"));
    butLocaRigh->move(49,27);
    connect(butLocaRigh,SIGNAL(clicked()),this,SLOT(fRowsLocR()));
    butLocaDown=new butToolX(grpRowsLoca);
    butLocaDown->setText(fL("butLocaDown"));
    butLocaDown->setIcon(QPixmap(":/Imag/QSTit_xdow.png"));
    butLocaDown->move(29,47);
    connect(butLocaDown,SIGNAL(clicked()),this,SLOT(fRowsLocD()));

    texRowsDime=new QLabel(fL("texRowsDime"),tabRows);
    texRowsDime->setMinimumWidth(70);
    texRowsDime->move(205,10);
    grpSkin *grpRowsDime=new grpSkin(tabRows,75,70,205,30);
    labRowsDimH=new QLabel("H.",grpRowsDime);
    labRowsDimH->setMaximumWidth(20);
    labRowsDimH->move(54,7);
    spiRowsDimH=new butSpin(grpRowsDime,6,7,objRowsWidt.mini,objRowsWidt.maxi,2,objRowsWidt.maxi);
    connect(spiRowsDimH,SIGNAL(valueChanged(int)),this,SLOT(fRowsDimH(int)));

    labRowsDimV=new QLabel("V.",grpRowsDime);
    labRowsDimV->setMaximumWidth(20);
    labRowsDimV->move(54,32);
    spiRowsDimV=new butSpin(grpRowsDime,6,32,objRowsHeig.mini,objRowsHeig.maxi,1,30);
    connect(spiRowsDimV,SIGNAL(valueChanged(int)),this,SLOT(fRowsDimV(int)));

    texRowsSpac=new QLabel(fL("texRowsSpac"),tabRows);
    texRowsSpac->setMinimumWidth(70);
    texRowsSpac->move(305,10);
    grpSkin *grpRowsSpac=new grpSkin(tabRows,75,40,305,30);
    spiRowsSpac=new butSpin(grpRowsSpac,6,7,objRowsSpac.mini,objRowsSpac.maxi,1,objRowsSpac.val0);
    connect(spiRowsSpac,SIGNAL(valueChanged(int)),this,SLOT(fRowsSpac(int)));

    texRowsBack=new QLabel(fL("texRowsBack"),tabRows);
    texRowsBack->setMinimumWidth(70);
    texRowsBack->move(405,10);
    grpSkin *grpRowsBack=new grpSkin(tabRows,75,40,405,30);
    butTextBack=new QPushButton(QPixmap(":/Imag/QSTit_colo.png")," "+fL("butTextBack"),grpRowsBack);
    butTextBack->move(3,3);
    connect(butTextBack,SIGNAL(clicked()),this,SLOT(fRowsBack()));

    labWindBack=new QLabel(fL("labWindBack"),tabRows);
    labWindBack->setMinimumWidth(70);
    labWindBack->move(600,10);
    grpSkin *grpWindBack=new grpSkin(tabRows,75,40,600,30);
    butWindBack=new QPushButton(QPixmap(":/Imag/QSTit_colo.png")," "+fL("butWindBack"),grpWindBack);
    butWindBack->move(3,3);
    connect(butWindBack,SIGNAL(clicked()),this,SLOT(fWindBackDial()));

    // page 1 - texts - texts -------------------------------------------------

    labSettLin1=new QLabel(tabRows);
    labSettLin1->setStyleSheet("background-color:#333333;");
    labSettLin1->setGeometry(10,110,665,1);

    texRowsText=new QLabel(fL("texRowsText"),tabRows);
    texRowsText->setMinimumWidth(70);
    texRowsText->move(10,120);

    labTextFont=new QLabel(fL("labTextFont"),tabRows);
    labTextFont->setMinimumWidth(70);
    labTextFont->move(105,120);
    grpSkin *grpTextFont=new grpSkin(tabRows,75,70,105,140);
    butFont=new QPushButton(QPixmap(":/Imag/QSTit_font.png")," "+fL("butFont"),grpTextFont);
    butFont->move(3,4);
    connect(butFont,SIGNAL(clicked()),this,SLOT(fRowsFont()));
    butTextColo=new QPushButton(QPixmap(":/Imag/QSTit_colo.png")," "+fL("butTextColo"),grpTextFont);
    butTextColo->move(3,28);
    connect(butTextColo,SIGNAL(clicked()),this,SLOT(fRowsColo()));

    labRowsOutl=new QLabel(fL("labRowsOutl"),tabRows);
    labRowsOutl->setMinimumWidth(70);
    labRowsOutl->move(205,120);
    grpSkin *grpRowsOutl=new grpSkin(tabRows,75,70,205,140);
    spiRowsOutl=new butSpin(grpRowsOutl,6,7,objRowsOutl.mini,objRowsOutl.maxi,1,objRowsOutl.val0);
    connect(spiRowsOutl,SIGNAL(valueChanged(int)),this,SLOT(fRowsOutlThik(int)));
    butRowsOutl=new QPushButton(QPixmap(":/Imag/QSTit_colo.png")," "+fL("butRowsOutl"),grpRowsOutl);
    butRowsOutl->move(3,28);
    connect(butRowsOutl,SIGNAL(clicked()),this,SLOT(fRowsOutl()));

    texRowsRota=new QLabel(fL("texRowsRota"),tabRows);
    texRowsRota->setMinimumWidth(70);
    texRowsRota->move(305,120);
    grpSkin *grpRowsRota=new grpSkin(tabRows,75,40,305,140);
    spiRowsRota=new butSpin(grpRowsRota,6,7,objRowsRota.mini,objRowsRota.maxi,1,objRowsRota.val0);
    connect(spiRowsRota,SIGNAL(valueChanged(int)),this,SLOT(fRowsRota(int)));

    labTextAliH=new QLabel(fL("labTextAliH"),tabRows);
    labTextAliH->setMinimumWidth(80);
    labTextAliH->move(405,120);
    grpSkin *grpTextAliH=new grpSkin(tabRows,75,40,405,140);
    butHoriLeft=new butToolX(grpTextAliH);
    butHoriLeft->setText(fL("butHoriLeft"));
    butHoriLeft->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
    butHoriLeft->move(7,7);
    connect(butHoriLeft,SIGNAL(clicked()),this,SLOT(fRowsHoriLef0()));
    butHoriCent=new butToolX(grpTextAliH);
    butHoriCent->setText(fL("butHoriCent"));
    butHoriCent->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
    butHoriCent->move(29,7);
    connect(butHoriCent,SIGNAL(clicked()),this,SLOT(fRowsHoriCen0()));
    butHoriRigh=new butToolX(grpTextAliH);
    butHoriRigh->setText(fL("butHoriRigh"));
    butHoriRigh->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
    butHoriRigh->move(51,7);
    connect(butHoriRigh,SIGNAL(clicked()),this,SLOT(fRowsHoriRig0()));

    labTextAliV=new QLabel(fL("labTextAliV"),tabRows);
    labTextAliV->setMinimumWidth(80);
    labTextAliV->move(505,120);
    grpSkin *boxTextAliV=new grpSkin(tabRows,75,40,505,140);
    butVertTopy=new butToolX(boxTextAliV);
    butVertTopy->setText(fL("butVertTopy"));
    butVertTopy->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
    butVertTopy->move(7,7);
    connect(butVertTopy,SIGNAL(clicked()),this,SLOT(fRowsVertTop0()));
    butVertCent=new butToolX(boxTextAliV);
    butVertCent->setText(fL("butVertCent"));
    butVertCent->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
    butVertCent->move(29,7);
    connect(butVertCent,SIGNAL(clicked()),this,SLOT(fRowsVertCen0()));
    butVertBott=new butToolX(boxTextAliV);
    butVertBott->setText(fL("butVertBott"));
    butVertBott->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
    butVertBott->move(51,7);
    connect(butVertBott,SIGNAL(clicked()),this,SLOT(fRowsVertBot0()));

    QPushButton *labVers=new QPushButton("    Vers. "+gVers,tabRows);
    labVers->setStyleSheet("color:#0055aa;border:1px solid #0055aa;padding:3px;");
    labVers->move(598,214);

    // page 2 - general -------------------------------------------------------

    tabGene=new QWidget;
    tabGene->setStyleSheet("border:none;background-color:#151515;");

    labGridFont=new QLabel(fL("labGridFont"),tabGene);
    labGridFont->setMinimumWidth(70);
    labGridFont->move(10,10);
    grpSkin *grpGridFont=new grpSkin(tabGene,75,40,10,30);
    butGridFont=new QPushButton(QPixmap(":/Imag/QSTit_font.png")," "+fL("butFont"),grpGridFont);
    butGridFont->move(3,3);
    connect(butGridFont,SIGNAL(clicked()),this,SLOT(fGridFontDial()));

    labGridColo=new QLabel(fL("labGridColo"),tabGene);
    labGridColo->setMinimumWidth(70);
    labGridColo->move(110,10);
    grpSkin *grpGridColo=new grpSkin(tabGene,75,40,110,30);
    radGridDark=new QRadioButton(fL("radGridDark"),grpGridColo);
    radGridDark->move(3,3);
    radGridDark->setChecked(gGridColoDark);
    connect(radGridDark,SIGNAL(clicked()),this,SLOT(fGridColoTogg()));
    radGridWhit=new QRadioButton(fL("radGridWhit"),grpGridColo);
    radGridWhit->move(3,19);
    connect(radGridWhit,SIGNAL(clicked()),this,SLOT(fGridColoTogg()));

    labWorkLang=new QLabel(fL("labWorkLang"),tabGene);
    labWorkLang->setMinimumWidth(70);
    labWorkLang->move(310,10);
    grpSkin *grpWorkLang=new grpSkin(tabGene,75,40,310,30);
    radLangEngl=new QRadioButton("English",grpWorkLang);
    radLangEngl->move(3,3);
    connect(radLangEngl,SIGNAL(clicked()),this,SLOT(fLAll()));
    radLangOthe=new QRadioButton(fL("radLangOthe"),grpWorkLang);
    radLangOthe->move(3,19);
    connect(radLangOthe,SIGNAL(clicked()),this,SLOT(fLAll()));

    oLang.setFileName("./QSTit_Lang.txt");
    if (!oLang.exists()) {radLangOthe->setDisabled(true);radLangOthe->setStyleSheet(gExplDisa);}

    if (gLang==0) radLangEngl->setChecked(true);
    if (gLang==1) radLangOthe->setChecked(true);

    #ifdef Q_OS_WIN32
    labTaskShow=new QLabel(fL("labTaskShow"),tabGene);
    labTaskShow->setMinimumWidth(80);
    labTaskShow->move(410,10);
    grpSkin *grpTaskShow=new grpSkin(tabGene,75,40,410,30);
    radTaskShow=new QRadioButton(fL("radTaskShow"),grpTaskShow);
    radTaskShow->move(3,3);
    connect(radTaskShow,SIGNAL(clicked()),this,SLOT(fWindTask()));
    radTaskHide=new QRadioButton(fL("radTaskHide"),grpTaskShow);
    radTaskHide->move(3,19);
    radTaskHide->setChecked(true);
    connect(radTaskHide,SIGNAL(clicked()),this,SLOT(fWindTask()));
    #endif

    // page 2 - general - others ----------------------------------------------

    labSettLin2=new QLabel(tabGene);
    labSettLin2->setStyleSheet("background-color:#333333;");
    labSettLin2->setGeometry(10,110,665,1);

    chkSecoText=new QCheckBox(fL("chkSecoText"),tabGene);
    chkSecoText->setMinimumWidth(200);
    chkSecoText->move(10,120);
    connect(chkSecoText,SIGNAL(stateChanged(int)),this,SLOT(fRowsSeco(int)));

    chkSecoItal=new QCheckBox(fL("chkSecoItal"),tabGene);
    chkSecoItal->setMinimumWidth(200);
    chkSecoItal->move(10,140);
    connect(chkSecoItal,SIGNAL(stateChanged(int)),this,SLOT(fRowsItal(int)));

    labJumpBase=new QLabel(fL("labJumpBase"),tabGene);
    labJumpBase->setMinimumWidth(140);
    labJumpBase->move(357,120);
    spiJumpBase=new QSpinBox(tabGene);
    spiJumpBase->setStyleSheet(gSpinStyl);
    spiJumpBase->setRange(1,10);
    spiJumpBase->setValue(gJumpBase/100);
    spiJumpBase->move(310,120);
    connect(spiJumpBase,SIGNAL(valueChanged(int)),this,SLOT(fJumpBase(int)));

    // page 3 - shed ----------------------------------------------------------

    tabShed=new QWidget;
    tabShed->setStyleSheet("border:none;background-color:#151515;");
    fSettCreaShed();

    // page 4 - save ----------------------------------------------------------

    tabSave=new QWidget;
    tabSave->setStyleSheet("border:none;background-color:#151515;");
    fSettCreaSave();

    // add pages --------------------------------------------------------------

    tabSett->addTab(tabRows,fL("tabSett0"));
    tabSett->addTab(tabGene,fL("tabSett1"));
    tabSett->addTab(tabShed,fL("tabSett2"));
    tabSett->addTab(tabSave,fL("tabSett3"));
}
void winMain::fSettCreaSave()
{
    QString sStyl="color:#ffffff;border:none;width:180px;";

    labSettLin4=new QLabel(tabSave);
    labSettLin4->setStyleSheet("background-color:#333333;");
    labSettLin4->setGeometry(10,110,665,1);

    grpSkin *grpSettSave=new grpSkin(tabSave,205,70,10,10);
    radSaveExiP=new QRadioButton(fL("radExitSavP"),grpSettSave);
    radSaveExiP->setStyleSheet(sStyl);
    radSaveExiP->move(3,4);
    connect(radSaveExiP,SIGNAL(clicked()),this,SLOT(fSettSaveGlob()));
    radSaveExiF=new QRadioButton(fL("radExitSavF"),grpSettSave);
    radSaveExiF->setStyleSheet(sStyl);
    radSaveExiF->move(3,28);
    connect(radSaveExiF,SIGNAL(clicked()),this,SLOT(fSettSaveFile()));

    grpSkin *grpSettBase=new grpSkin(tabSave,205,40,10,120);
    butSettBase=new QPushButton(QPixmap(":/Imag/QSTit_base.png")," "+fL("butSettBase"),grpSettBase);
    butSettBase->setStyleSheet(sStyl);
    butSettBase->move(3,3);
    connect(butSettBase,SIGNAL(clicked()),this,SLOT(fSettBaseDial()));
}
void winMain::fSettCreaShed()
{
    int iI[]={28,46,64,82,100,118,136,154,172,190,208};
    int iX[]={10,140,249,339,429,519,609};
    int iY[]={28,48,48,70,94,118,142,167,189,212,212};
    int iL[]={600,240,330,420,510};

    labRowsLoca=new QLabel(tabShed);
                labRowsLoca->setMinimumWidth(120);
                labRowsLoca->setStyleSheet(gExplStyl);
                labRowsLoca->move(iX[0],iI[0]);
    labRowsSize=new QLabel(tabShed);
                labRowsSize->setMinimumWidth(120);
                labRowsSize->setStyleSheet(gExplStyl);
                labRowsSize->move(iX[0],iI[1]);
    labRowsCent=new QLabel(tabShed);
                labRowsCent->setMinimumWidth(120);
                labRowsCent->setStyleSheet(gExplStyl);
                labRowsCent->move(iX[0],iI[2]);
    labMenuSize=new QLabel(tabShed);
                labMenuSize->setMinimumWidth(120);
                labMenuSize->setStyleSheet(gExplStyl);
                labMenuSize->move(iX[0],iI[3]);
    labMenuLoca=new QLabel(tabShed);
                labMenuLoca->setMinimumWidth(120);
                labMenuLoca->setStyleSheet(gExplStyl);
                labMenuLoca->move(iX[0],iI[4]);
    labScreSize=new QLabel(tabShed);
                labScreSize->setMinimumWidth(120);
                labScreSize->setStyleSheet(gExplStyl);
                labScreSize->move(iX[0],iI[5]);
    labGridSize=new QLabel(tabShed);
                labGridSize->setMinimumWidth(120);
                labGridSize->setStyleSheet(gExplStyl);
                labGridSize->move(iX[0],iI[6]);
    labGridCol3=new QLabel(tabShed);
                labGridCol3->setMinimumWidth(120);
                labGridCol3->setStyleSheet(gExplStyl);
                labGridCol3->move(iX[0],iI[7]);
    labGridCol4=new QLabel(tabShed);
                labGridCol4->setMinimumWidth(120);
                labGridCol4->setStyleSheet(gExplStyl);
                labGridCol4->move(iX[0],iI[8]);
    labGridCol5=new QLabel(tabShed);
                labGridCol5->setMinimumWidth(120);
                labGridCol5->setStyleSheet(gExplStyl);
                labGridCol5->move(iX[0],iI[9]);
    labGridCol6=new QLabel(tabShed);
                labGridCol6->setMinimumWidth(120);
                labGridCol6->setStyleSheet(gExplStyl);
                labGridCol6->move(iX[0],iI[10]);

    labShedShow=new QLabel(fL("labShedShow"),tabShed);
                labShedShow->setGeometry(iX[1],iY[0],92,20);
                labShedShow->setAlignment(Qt::AlignRight);
    labShedText=new QLabel(fL("labShedText"),tabShed);
                labShedText->setGeometry(iX[1],iY[1]+2,92,20);
                labShedText->setAlignment(Qt::AlignRight);
    labShedBack=new QLabel(fL("labShedBack"),tabShed);
                labShedBack->setGeometry(iX[1],iY[3]+2,92,20);
                labShedBack->setAlignment(Qt::AlignRight);
    labShedHeig=new QLabel(fL("labShedHeig"),tabShed);
                labShedHeig->setGeometry(iX[1],iY[4]+2,92,20);
                labShedHeig->setAlignment(Qt::AlignRight);
    labShedSpac=new QLabel(fL("labShedSpac"),tabShed);
                labShedSpac->setGeometry(iX[1],iY[5]+2,92,20);
                labShedSpac->setAlignment(Qt::AlignRight);
    labShedRota=new QLabel(fL("labShedRota"),tabShed);
                labShedRota->setGeometry(iX[1],iY[6]+2,92,20);
                labShedRota->setAlignment(Qt::AlignRight);
    labShedHori=new QLabel(fL("labTextAliH"),tabShed);
                labShedHori->setGeometry(iX[1],iY[7]+2,92,20);
                labShedHori->setAlignment(Qt::AlignRight);
    labShedVert=new QLabel(fL("labTextAliV"),tabShed);
                labShedVert->setGeometry(iX[1],iY[8]+2,92,20);
                labShedVert->setAlignment(Qt::AlignRight);
    labShedOutl=new QLabel(fL("labRowsOutl"),tabShed);
                labShedOutl->setGeometry(iX[1],iY[9]+2,92,20);
                labShedOutl->setAlignment(Qt::AlignRight);

    labShedLin1=new QLabel(tabShed);
                labShedLin1->setStyleSheet("background-color:#333333;");
                labShedLin1->setGeometry(iL[1],10,1,230);
    labShedTit1=new QLabel(fL("labShedTit1"),tabShed);
                labShedTit1->setMinimumWidth(80);
                labShedTit1->move(iX[2],10);
    radShedSho1=new QRadioButton(tabShed);
                radShedSho1->move(iX[2],iY[0]);
                radShedSho1->setAutoExclusive(false);
                radShedSho1->setChecked(objRow1.show);
                connect(radShedSho1,SIGNAL(clicked()),this,SLOT(fShedNumb()));
    butShedFon1=new QPushButton(QPixmap(":/Imag/QSTit_font.png"),"",tabShed);
                butShedFon1->move(iX[2]-1,iY[1]);
                connect(butShedFon1,SIGNAL(clicked()),this,SLOT(fRowsFon1()));
    butShedFor1=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedFor1->move(iX[2]+42,iY[2]);
                connect(butShedFor1,SIGNAL(clicked()),this,SLOT(fRowsCol1()));
    butShedBac1=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedBac1->move(iX[2]-1,iY[3]);
                connect(butShedBac1,SIGNAL(clicked()),this,SLOT(fRowsBac1()));
    spiShedHei1=new QSpinBox(tabShed);
                spiShedHei1->move(iX[2],iY[4]);
                spiShedHei1->setStyleSheet(gSpinStyl);
                spiShedHei1->setRange(objRowsHeig.mini,objRowsHeig.maxi);
                spiShedHei1->setValue(objRow1.heig);
                connect(spiShedHei1,SIGNAL(valueChanged(int)),this,SLOT(fShedHeig(int)));
    spiShedSpa1=new QSpinBox(tabShed);
                spiShedSpa1->move(iX[2],iY[5]);
                spiShedSpa1->setStyleSheet(gSpinStyl);
                spiShedSpa1->setRange(objRowsSpac.mini,objRowsSpac.maxi);
                spiShedSpa1->setValue(objRow1.spac);
                connect(spiShedSpa1,SIGNAL(valueChanged(int)),this,SLOT(fShedSpac(int)));
    spiShedRot1=new QSpinBox(tabShed);
                spiShedRot1->move(iX[2],iY[6]);
                spiShedRot1->setStyleSheet(gSpinStyl);
                spiShedRot1->setRange(objRowsRota.mini,objRowsRota.maxi);
                spiShedRot1->setValue(objRowsRota.val0);
                connect(spiShedRot1,SIGNAL(valueChanged(int)),this,SLOT(fShedRota(int)));
    butShedHoL1=new butToolX(tabShed);
                butShedHoL1->setText(fL("butHoriLeft"));
                butShedHoL1->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
                butShedHoL1->move(iX[2],iY[7]);
                connect(butShedHoL1,SIGNAL(clicked()),this,SLOT(fRowsHoriLef1()));
    butShedHoC1=new butToolX(tabShed);
                butShedHoC1->setText(fL("butHoriCent"));
                butShedHoC1->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
                butShedHoC1->move(iX[2]+22,iY[7]);
                connect(butShedHoC1,SIGNAL(clicked()),this,SLOT(fRowsHoriCen1()));
    butShedHoR1=new butToolX(tabShed);
                butShedHoR1->setText(fL("butHoriRigh"));
                butShedHoR1->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
                butShedHoR1->move(iX[2]+44,iY[7]);
                connect(butShedHoR1,SIGNAL(clicked()),this,SLOT(fRowsHoriRig1()));
    butShedVeT1=new butToolX(tabShed);
                butShedVeT1->setText(fL("butVertTopy"));
                butShedVeT1->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
                butShedVeT1->move(iX[2],iY[8]);
                connect(butShedVeT1,SIGNAL(clicked()),this,SLOT(fRowsVertTop1()));
    butShedVeC1=new butToolX(tabShed);
                butShedVeC1->setText(fL("butVertCent"));
                butShedVeC1->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
                butShedVeC1->move(iX[2]+22,iY[8]);
                connect(butShedVeC1,SIGNAL(clicked()),this,SLOT(fRowsVertCen1()));
    butShedVeB1=new butToolX(tabShed);
                butShedVeB1->setText(fL("butVertBott"));
                butShedVeB1->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
                butShedVeB1->move(iX[2]+44,iY[8]);
                connect(butShedVeB1,SIGNAL(clicked()),this,SLOT(fRowsVertBot1()));
    spiShedOut1=new QSpinBox(tabShed);
                spiShedOut1->move(iX[2],iY[9]);
                spiShedOut1->setStyleSheet(gSpinStyl);
                spiShedOut1->setRange(objRowsOutl.mini,objRowsOutl.maxi);
                spiShedOut1->setValue(objRow1.outl);
                connect(spiShedOut1,SIGNAL(valueChanged(int)),this,SLOT(fShedOutl(int)));
    butShedOut1=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedOut1->move(iX[2]+42,iY[9]);
                connect(butShedOut1,SIGNAL(clicked()),this,SLOT(fRowsOut1()));

    labShedLin2=new QLabel(tabShed);
                labShedLin2->setStyleSheet("background-color:#333333;");
                labShedLin2->setGeometry(iL[2],10,1,230);
    labShedTit2=new QLabel(fL("labShedTit2"),tabShed);
                labShedTit2->setMinimumWidth(80);
                labShedTit2->move(iX[3],10);
    radShedSho2=new QRadioButton(tabShed);
                radShedSho2->move(iX[3],iY[0]);
                radShedSho2->setAutoExclusive(false);
                radShedSho2->setChecked(objRow2.show);
                connect(radShedSho2,SIGNAL(clicked()),this,SLOT(fShedNumb()));
    butShedFon2=new QPushButton(QPixmap(":/Imag/QSTit_font.png"),"",tabShed);
                butShedFon2->move(iX[3]-1,iY[1]);
                connect(butShedFon2,SIGNAL(clicked()),this,SLOT(fRowsFon2()));
    butShedFor2=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedFor2->move(iX[3]+42,iY[2]);
                connect(butShedFor2,SIGNAL(clicked()),this,SLOT(fRowsCol2()));
    butShedBac2=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedBac2->move(iX[3]-1,iY[3]);
                connect(butShedBac2,SIGNAL(clicked()),this,SLOT(fRowsBac2()));
    spiShedHei2=new QSpinBox(tabShed);
                spiShedHei2->move(iX[3],iY[4]);
                spiShedHei2->setStyleSheet(gSpinStyl);
                spiShedHei2->setRange(objRowsHeig.mini,objRowsHeig.maxi);
                spiShedHei2->setValue(objRow2.heig);
                connect(spiShedHei2,SIGNAL(valueChanged(int)),this,SLOT(fShedHeig(int)));
    spiShedSpa2=new QSpinBox(tabShed);
                spiShedSpa2->move(iX[3],iY[5]);
                spiShedSpa2->setStyleSheet(gSpinStyl);
                spiShedSpa2->setRange(objRowsSpac.mini,objRowsSpac.maxi);
                spiShedSpa2->setValue(objRow2.spac);
                connect(spiShedSpa2,SIGNAL(valueChanged(int)),this,SLOT(fShedSpac(int)));
    spiShedRot2=new QSpinBox(tabShed);
                spiShedRot2->move(iX[3],iY[6]);
                spiShedRot2->setStyleSheet(gSpinStyl);
                spiShedRot2->setRange(objRowsRota.mini,objRowsRota.maxi);
                spiShedRot2->setValue(objRowsRota.val0);
                connect(spiShedRot2,SIGNAL(valueChanged(int)),this,SLOT(fShedRota(int)));
    butShedHoL2=new butToolX(tabShed);
                butShedHoL2->setText(fL("butHoriLeft"));
                butShedHoL2->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
                butShedHoL2->move(iX[3],iY[7]);
                connect(butShedHoL2,SIGNAL(clicked()),this,SLOT(fRowsHoriLef2()));
    butShedHoC2=new butToolX(tabShed);
                butShedHoC2->setText(fL("butHoriCent"));
                butShedHoC2->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
                butShedHoC2->move(iX[3]+22,iY[7]);
                connect(butShedHoC2,SIGNAL(clicked()),this,SLOT(fRowsHoriCen2()));
    butShedHoR2=new butToolX(tabShed);
                butShedHoR2->setText(fL("butHoriRigh"));
                butShedHoR2->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
                butShedHoR2->move(iX[3]+44,iY[7]);
                connect(butShedHoR2,SIGNAL(clicked()),this,SLOT(fRowsHoriRig2()));
    butShedVeT2=new butToolX(tabShed);
                butShedVeT2->setText(fL("butVertTopy"));
                butShedVeT2->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
                butShedVeT2->move(iX[3],iY[8]);
                connect(butShedVeT2,SIGNAL(clicked()),this,SLOT(fRowsVertTop2()));
    butShedVeC2=new butToolX(tabShed);
                butShedVeC2->setText(fL("butVertCent"));
                butShedVeC2->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
                butShedVeC2->move(iX[3]+22,iY[8]);
                connect(butShedVeC2,SIGNAL(clicked()),this,SLOT(fRowsVertCen2()));
    butShedVeB2=new butToolX(tabShed);
                butShedVeB2->setText(fL("butVertBott"));
                butShedVeB2->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
                butShedVeB2->move(iX[3]+44,iY[8]);
                connect(butShedVeB2,SIGNAL(clicked()),this,SLOT(fRowsVertBot2()));
    spiShedOut2=new QSpinBox(tabShed);
                spiShedOut2->move(iX[3],iY[9]);
                spiShedOut2->setStyleSheet(gSpinStyl);
                spiShedOut2->setRange(objRowsOutl.mini,objRowsOutl.maxi);
                spiShedOut2->setValue(objRow2.outl);
                connect(spiShedOut2,SIGNAL(valueChanged(int)),this,SLOT(fShedOutl(int)));
    butShedOut2=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedOut2->move(iX[3]+42,iY[9]);
                connect(butShedOut2,SIGNAL(clicked()),this,SLOT(fRowsOut2()));

    labShedLin3=new QLabel(tabShed);
                labShedLin3->setStyleSheet("background-color:#333333;");
                labShedLin3->setGeometry(iL[3],10,1,230);
    labShedTit3=new QLabel(fL("labShedTit3"),tabShed);
                labShedTit3->setMinimumWidth(80);
                labShedTit3->move(iX[4],10);
    radShedSho3=new QRadioButton(tabShed);
                radShedSho3->move(iX[4],iY[0]);
                radShedSho3->setAutoExclusive(false);
                radShedSho3->setChecked(objRow3.show);
                connect(radShedSho3,SIGNAL(clicked()),this,SLOT(fShedNumb()));
    butShedFon3=new QPushButton(QPixmap(":/Imag/QSTit_font.png"),"",tabShed);
                butShedFon3->move(iX[4]-1,iY[1]);
                connect(butShedFon3,SIGNAL(clicked()),this,SLOT(fRowsFon3()));
    butShedFor3=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedFor3->move(iX[4]+42,iY[2]);
                connect(butShedFor3,SIGNAL(clicked()),this,SLOT(fRowsCol3()));
    butShedBac3=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedBac3->move(iX[4]-1,iY[3]);
                connect(butShedBac3,SIGNAL(clicked()),this,SLOT(fRowsBac3()));
    spiShedHei3=new QSpinBox(tabShed);
                spiShedHei3->move(iX[4],iY[4]);
                spiShedHei3->setStyleSheet(gSpinStyl);
                spiShedHei3->setRange(objRowsHeig.mini,objRowsHeig.maxi);
                spiShedHei3->setValue(objRow3.heig);
                connect(spiShedHei3,SIGNAL(valueChanged(int)),this,SLOT(fShedHeig(int)));
    spiShedSpa3=new QSpinBox(tabShed);
                spiShedSpa3->move(iX[4],iY[5]);
                spiShedSpa3->setStyleSheet(gSpinStyl);
                spiShedSpa3->setRange(objRowsSpac.mini,objRowsSpac.maxi);
                spiShedSpa3->setValue(objRow3.spac);
                connect(spiShedSpa3,SIGNAL(valueChanged(int)),this,SLOT(fShedSpac(int)));
    spiShedRot3=new QSpinBox(tabShed);
                spiShedRot3->move(iX[4],iY[6]);
                spiShedRot3->setStyleSheet(gSpinStyl);
                spiShedRot3->setRange(objRowsRota.mini,objRowsRota.maxi);
                spiShedRot3->setValue(objRowsRota.val0);
                connect(spiShedRot3,SIGNAL(valueChanged(int)),this,SLOT(fShedRota(int)));
    butShedHoL3=new butToolX(tabShed);
                butShedHoL3->setText(fL("butHoriLeft"));
                butShedHoL3->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
                butShedHoL3->move(iX[4],iY[7]);
                connect(butShedHoL3,SIGNAL(clicked()),this,SLOT(fRowsHoriLef3()));
    butShedHoC3=new butToolX(tabShed);
                butShedHoC3->setText(fL("butHoriCent"));
                butShedHoC3->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
                butShedHoC3->move(iX[4]+22,iY[7]);
                connect(butShedHoC3,SIGNAL(clicked()),this,SLOT(fRowsHoriCen3()));
    butShedHoR3=new butToolX(tabShed);
                butShedHoR3->setText(fL("butHoriRigh"));
                butShedHoR3->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
                butShedHoR3->move(iX[4]+44,iY[7]);
                connect(butShedHoR3,SIGNAL(clicked()),this,SLOT(fRowsHoriRig3()));
    butShedVeT3=new butToolX(tabShed);
                butShedVeT3->setText(fL("butVertTopy"));
                butShedVeT3->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
                butShedVeT3->move(iX[4],iY[8]);
                connect(butShedVeT3,SIGNAL(clicked()),this,SLOT(fRowsVertTop3()));
    butShedVeC3=new butToolX(tabShed);
                butShedVeC3->setText(fL("butVertCent"));
                butShedVeC3->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
                butShedVeC3->move(iX[4]+22,iY[8]);
                connect(butShedVeC3,SIGNAL(clicked()),this,SLOT(fRowsVertCen3()));
    butShedVeB3=new butToolX(tabShed);
                butShedVeB3->setText(fL("butVertBott"));
                butShedVeB3->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
                butShedVeB3->move(iX[4]+44,iY[8]);
                connect(butShedVeB3,SIGNAL(clicked()),this,SLOT(fRowsVertBot3()));
    spiShedOut3=new QSpinBox(tabShed);
                spiShedOut3->move(iX[4],iY[9]);
                spiShedOut3->setStyleSheet(gSpinStyl);
                spiShedOut3->setRange(objRowsOutl.mini,objRowsOutl.maxi);
                spiShedOut3->setValue(objRow3.outl);
                connect(spiShedOut3,SIGNAL(valueChanged(int)),this,SLOT(fShedOutl(int)));
    butShedOut3=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedOut3->move(iX[4]+42,iY[9]);
                connect(butShedOut3,SIGNAL(clicked()),this,SLOT(fRowsOut3()));

    labShedLin4=new QLabel(tabShed);
                labShedLin4->setStyleSheet("background-color:#333333;");
                labShedLin4->setGeometry(iL[4],10,1,230);
    labShedTit4=new QLabel(fL("labShedTit4"),tabShed);
                labShedTit4->setMinimumWidth(80);
                labShedTit4->move(iX[5],10);
    radShedSho4=new QRadioButton(tabShed);
                radShedSho4->move(iX[5],iY[0]);
                radShedSho4->setAutoExclusive(false);
                radShedSho4->setChecked(objRow4.show);
                connect(radShedSho4,SIGNAL(clicked()),this,SLOT(fShedNumb()));
    butShedFon4=new QPushButton(QPixmap(":/Imag/QSTit_font.png"),"",tabShed);
                butShedFon4->move(iX[5]-1,iY[1]);
                connect(butShedFon4,SIGNAL(clicked()),this,SLOT(fRowsFon4()));
    butShedFor4=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedFor4->move(iX[5]+42,iY[2]);
                connect(butShedFor4,SIGNAL(clicked()),this,SLOT(fRowsCol4()));
    butShedBac4=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedBac4->move(iX[5]-1,iY[3]);
                connect(butShedBac4,SIGNAL(clicked()),this,SLOT(fRowsBac4()));
    spiShedHei4=new QSpinBox(tabShed);
                spiShedHei4->move(iX[5],iY[4]);
                spiShedHei4->setStyleSheet(gSpinStyl);
                spiShedHei4->setRange(objRowsHeig.mini,objRowsHeig.maxi);
                spiShedHei4->setValue(objRow4.heig);
                connect(spiShedHei4,SIGNAL(valueChanged(int)),this,SLOT(fShedHeig(int)));
    spiShedRot4=new QSpinBox(tabShed);
                spiShedRot4->move(iX[5],iY[6]);
                spiShedRot4->setStyleSheet(gSpinStyl);
                spiShedRot4->setRange(objRowsRota.mini,objRowsRota.maxi);
                spiShedRot4->setValue(objRowsRota.val0);
                connect(spiShedRot4,SIGNAL(valueChanged(int)),this,SLOT(fShedRota(int)));
    butShedHoL4=new butToolX(tabShed);
                butShedHoL4->setText(fL("butHoriLeft"));
                butShedHoL4->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
                butShedHoL4->move(iX[5],iY[7]);
                connect(butShedHoL4,SIGNAL(clicked()),this,SLOT(fRowsHoriLef4()));
    butShedHoC4=new butToolX(tabShed);
                butShedHoC4->setText(fL("butHoriCent"));
                butShedHoC4->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
                butShedHoC4->move(iX[5]+22,iY[7]);
                connect(butShedHoC4,SIGNAL(clicked()),this,SLOT(fRowsHoriCen4()));
    butShedHoR4=new butToolX(tabShed);
                butShedHoR4->setText(fL("butHoriRigh"));
                butShedHoR4->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
                butShedHoR4->move(iX[5]+44,iY[7]);
                connect(butShedHoR4,SIGNAL(clicked()),this,SLOT(fRowsHoriRig4()));
    butShedVeT4=new butToolX(tabShed);
                butShedVeT4->setText(fL("butVertTopy"));
                butShedVeT4->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
                butShedVeT4->move(iX[5],iY[8]);
                connect(butShedVeT4,SIGNAL(clicked()),this,SLOT(fRowsVertTop4()));
    butShedVeC4=new butToolX(tabShed);
                butShedVeC4->setText(fL("butVertCent"));
                butShedVeC4->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
                butShedVeC4->move(iX[5]+22,iY[8]);
                connect(butShedVeC4,SIGNAL(clicked()),this,SLOT(fRowsVertCen4()));
    butShedVeB4=new butToolX(tabShed);
                butShedVeB4->setText(fL("butVertBott"));
                butShedVeB4->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
                butShedVeB4->move(iX[5]+44,iY[8]);
                connect(butShedVeB4,SIGNAL(clicked()),this,SLOT(fRowsVertBot4()));
    spiShedOut4=new QSpinBox(tabShed);
                spiShedOut4->move(iX[5],iY[9]);
                spiShedOut4->setStyleSheet(gSpinStyl);
                spiShedOut4->setRange(objRowsOutl.mini,objRowsOutl.maxi);
                spiShedOut4->setValue(objRow4.outl);
                connect(spiShedOut4,SIGNAL(valueChanged(int)),this,SLOT(fShedOutl(int)));
    butShedOut4=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedOut4->move(iX[5]+42,iY[9]);
                connect(butShedOut4,SIGNAL(clicked()),this,SLOT(fRowsOut4()));

    labShedLin0=new QLabel(tabShed);
                labShedLin0->setStyleSheet("background-color:#333333;");
                labShedLin0->setGeometry(iL[0],10,1,230);
    labShedTit0=new QLabel(fL("labShedTit0"),tabShed);
                labShedTit0->setMinimumWidth(80);
                labShedTit0->move(iX[6],10);
    butShedFon0=new QPushButton(QPixmap(":/Imag/QSTit_font.png"),"",tabShed);
                butShedFon0->move(iX[6]-1,iY[1]);
                connect(butShedFon0,SIGNAL(clicked()),this,SLOT(fRowsFont()));
    butShedFor0=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedFor0->move(iX[6]+42,iY[2]);
                connect(butShedFor0,SIGNAL(clicked()),this,SLOT(fRowsColo()));
    butShedBac0=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedBac0->move(iX[6]-1,iY[3]);
                connect(butShedBac0,SIGNAL(clicked()),this,SLOT(fRowsBack()));
    spiShedHei0=new QSpinBox(tabShed);
                spiShedHei0->move(iX[6],iY[4]);
                spiShedHei0->setStyleSheet(gSpinStyl);
                spiShedHei0->setRange(objRowsHeig.mini,objRowsHeig.maxi);
                spiShedHei0->setValue(objRow0.heig);
                connect(spiShedHei0,SIGNAL(valueChanged(int)),this,SLOT(fRowsDimV(int)));
    spiShedSpa0=new QSpinBox(tabShed);
                spiShedSpa0->move(iX[6],iY[5]);
                spiShedSpa0->setStyleSheet(gSpinStyl);
                spiShedSpa0->setRange(objRowsSpac.mini,objRowsSpac.maxi);
                spiShedSpa0->setValue(objRowsSpac.val0);
                connect(spiShedSpa0,SIGNAL(valueChanged(int)),this,SLOT(fRowsSpac(int)));
    spiShedRot0=new QSpinBox(tabShed);
                spiShedRot0->move(iX[6],iY[6]);
                spiShedRot0->setStyleSheet(gSpinStyl);
                spiShedRot0->setRange(objRowsRota.mini,objRowsRota.maxi);
                spiShedRot0->setValue(objRowsRota.val0);
                connect(spiShedRot0,SIGNAL(valueChanged(int)),this,SLOT(fRowsRota(int)));
    butShedHoL0=new butToolX(tabShed);
                butShedHoL0->setText(fL("butHoriLeft"));
                butShedHoL0->setIcon(QPixmap(":/Imag/QSTit_hori_left.png"));
                butShedHoL0->move(iX[6],iY[7]);
                connect(butShedHoL0,SIGNAL(clicked()),this,SLOT(fRowsHoriLef0()));
    butShedHoC0=new butToolX(tabShed);
                butShedHoC0->setText(fL("butHoriCent"));
                butShedHoC0->setIcon(QPixmap(":/Imag/QSTit_hori_cent.png"));
                butShedHoC0->move(iX[6]+22,iY[7]);
                connect(butShedHoC0,SIGNAL(clicked()),this,SLOT(fRowsHoriCen0()));
    butShedHoR0=new butToolX(tabShed);
                butShedHoR0->setText(fL("butHoriRigh"));
                butShedHoR0->setIcon(QPixmap(":/Imag/QSTit_hori_righ.png"));
                butShedHoR0->move(iX[6]+44,iY[7]);
                connect(butShedHoR0,SIGNAL(clicked()),this,SLOT(fRowsHoriRig0()));
    butShedVeT0=new butToolX(tabShed);
                butShedVeT0->setText(fL("butVertTopy"));
                butShedVeT0->setIcon(QPixmap(":/Imag/QSTit_vert_topy.png"));
                butShedVeT0->move(iX[6],iY[8]);
                connect(butShedVeT0,SIGNAL(clicked()),this,SLOT(fRowsVertTop0()));
    butShedVeC0=new butToolX(tabShed);
                butShedVeC0->setText(fL("butVertCent"));
                butShedVeC0->setIcon(QPixmap(":/Imag/QSTit_vert_cent.png"));
                butShedVeC0->move(iX[6]+22,iY[8]);
                connect(butShedVeC0,SIGNAL(clicked()),this,SLOT(fRowsVertCen0()));
    butShedVeB0=new butToolX(tabShed);
                butShedVeB0->setText(fL("butVertBott"));
                butShedVeB0->setIcon(QPixmap(":/Imag/QSTit_vert_bott.png"));
                butShedVeB0->move(iX[6]+44,iY[8]);
                connect(butShedVeB0,SIGNAL(clicked()),this,SLOT(fRowsVertBot0()));
    spiShedOut0=new QSpinBox(tabShed);
                spiShedOut0->move(iX[6],iY[9]);
                spiShedOut0->setStyleSheet(gSpinStyl);
                spiShedOut0->setRange(objRowsOutl.mini,objRowsOutl.maxi);
                spiShedOut0->setValue(objRow0.outl);
                connect(spiShedOut0,SIGNAL(valueChanged(int)),this,SLOT(fRowsOutlThik(int)));
    butShedOut0=new QPushButton(QPixmap(":/Imag/QSTit_colo.png"),"",tabShed);
                butShedOut0->move(iX[6]+42,iY[9]);
                connect(butShedOut0,SIGNAL(clicked()),this,SLOT(fRowsOutl()));
}
void winMain::fSettBaseDial()
{
    messSkin cM;if (!cM.fMess(this,fraMenu,fL("msgCleaAllMess"),fL("butYeYe"),fL("butNoNo"))) return;
    fSettBase();
}
void winMain::fSettBase()
{
    fSettClos();
    if (gInfoDial) {diaInfo->close();}
    if (gHelpDial) {diaHelp->close();}
    gLang=0;
    gWork=gManu=gAuto=gSrtx=gPlay=gInit=false;
    gExitDial=gSettShow=gInfoDial=gHelpDial=false;
    gPuls=100;
    gAcce=gJump=0;
    gJumpBase=200;
    objRowsSpac.valu=objRowsSpac.val0;
    objRowsRota.valu=objRowsRota.val0;
    gSecoText=gSecoItal=false;
    gGridEdit=true;
    gGridSave=false;
    gGridColoDark=true;
    objRowsOutl.valu=0;

    labTime->setText("00:00:00");
    labPuls->setText("");
    labJump->setText("");

    objWind.basW=objWind.widt-2;
    gRowsFont.setFamily(qApp->font().family());

    fLangFileRead();
    fWindClear();
    fWindStyle();

    gGridModi=gGridMark=0;
    gGridRowsHeig=18;
    gGridFont=QFont(qApp->font().family(),9,QFont::Normal,false);
    fGridEditEnab();

    QString sConfFile=gConfFile;
    gConfFile=":/Help/QSTit_Default.cfg";fConfRead();
    gConfFile=sConfFile;
    if (gGridShow) {diaGrid->fRePosi();diaGrid->fMenuMove();}
}
void winMain::fSettShow()
{
    if (!gSett) return;
    fWindLogoHide();
    if (gInfoDial) {diaInfo->close();gInfoDial=false;}
    if (gExitDial) {fWindExitCanc();}
    if (!diaSett->isHidden()) {fSettClos();}
    else
    {
        diaSett->fRePosi();
        gSettShow=true;
        diaSett->show();
        diaSett->raise();
        diaSett->setFocus();
        if (!gWork) fWindBack();
    }
    fRowsInit();
}
void winMain::fSettClos()
{
    gSettShow=false;
    fRowsInit();
    diaSett->setHidden(true);
    if (!gWork) fWindClear();
    if (gGridShow) fGridFocus();
}
void winMain::fSettEnab()
{
    gSett=true;
    butSett->setIcon(QPixmap(":/Imag/QSTit_sett_enab.png"));
}
void winMain::fSettSaveFile() {fConfWrit(2);}
void winMain::fSettSaveGlob() {fConfWrit(1);}

//=================================================================================================
// file functions
//=================================================================================================

bool winMain::fFileConf()
{
    QString sConf=gFile.mid(0,gFile.size()-4)+QString(".cfg");
    oConf.setFileName(sConf);
    gConf=false;
    if (!oConf.exists()) return false;
    messSkin cM;if (!cM.fMess(this,fraMenu,fL("FileConfExisMess"),fL("butYeYe"),fL("butNoNo"))) return false;
    gConfFile=sConf;
    gConf=true;
    return true;
}
void winMain::fFileDial()
{
    if (gFileDial) {diaFile->close();gFileDial=false;return;}
    fWindLogoHide();
    if (gGridSave)
    {
        fGridModi();
    }
    else if (gGridShow)
    {
        messSkin cM;if (!cM.fMess(this,fraMenu,fL("FileProbOpenMess"),fL("butYeYe"),fL("butNoNo"))) return;
    }
    gFileDial=true;
    diaFile=new diaFileSkin(winWind,fraMenu,fL("diaFile"),fL("diaFileFolder"),fL("diaFileName"),fL("diaFileType"));
    connect(diaFile,SIGNAL(sFileGet(QString)),SLOT(fFileDialRepo(QString)));
    connect(diaFile,SIGNAL(sClosed()),SLOT(fFileDialCanc()));
}
void winMain::fFileDialCanc() {gFileDial=false;gFile="";fraMenu->setFocus();}
void winMain::fFileDialRepo(QString sRepo)
{
    gFileDial=false;
    gFile=sRepo;
    fraMenu->setFocus();
    if (gFile.isEmpty())
    {
        if (!gGridShow) diaGrid->hide();
    }
    else
    {
        fClearAll(false);
        fSettBase();
        if (fFileConf()) fConfRead();
        if (QFileInfo(gFile).suffix().toLower()==QString("srt")) gSrtx=true;
        else gSrtx=false;
        if (gSrtx) fFileReadSrtx();
        else fFileRead();
    }
}
void winMain::fFileRead()
{
    QString sLine,sGrid;
    int iGrid=0;
    int iLine=0;
    int iRows=0;
    int iColo=0;
    int iC,iT;
    QStringList lText;
    bool bStop=false;

    oFile.setFileName(gFile);

    if (!oFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        messSkin cM;cM.fMess(this,fraMenu,fL("FileProbWarnMess")+QString("|%1|%2").arg(gFile).arg(oFile.errorString()),fL("butOkOk"),"");
        return;
    }

    fFileEncoding(gFile);

    QProgressBar barFile(winWind);
    barFile.setGeometry(fraMenu->iX,fCalcPosY(21,fraMenu),fraMenu->iW,20);
    barFile.setRange(0,fFileSize(gFile));
    barFile.show();

    gWork=true;
    gManu=true;
    gAuto=false;
    gGridModi=0;
    gGridSave=false;
    fGridSaveIcon();
    gGridMark=0;
    fGridShow(false);
    fGridZero();
    gFileErro="";

    fFileTextMaxi(-1,0,0,0,0,0);

    QFontMetrics mGrid=QFontMetrics(gGridFont);
    QFontMetrics mRows=QFontMetrics(gRowsFont);

    QTextStream oStrm(&oFile);
    if (gFileEnco) oStrm.setCodec("ISO-8859-1");
    else oStrm.setCodec("UTF-8");

    while (!oStrm.atEnd() && !bStop)
    {
        barFile.setValue(++iRows);

        iLine++;
        sLine=oStrm.readLine(0).trimmed();
        lText=sLine.split(QString("\\"));

        griText->insertRow(++iGrid);
        fGridItemSetx("",iGrid,0);
        fGridItemSetx("",iGrid,1);
        fGridItemSetx("",iGrid,2);
        fGridItemSetx("",iGrid,3);
        fGridItemSetx("",iGrid,4);
        fGridItemSetx("",iGrid,5);
        fGridItemSetx("",iGrid,6);
        for (iT=0; iT<4; iT++)
        {
            iC=iT+3;
            if (lText.size()>iT)
            {
                sLine=fFileLineForm(lText[iT]);
                fGridItemSetx(sLine,iGrid,iC);
                sGrid=sLine;sLine=fGridTextClean(lText[iT]);
                bStop=fFileTextMaxi(mGrid.width(sGrid),mRows.width(sLine),sLine.length(),iGrid,iLine,iC);
                if (bStop) break;
            }
            else
            {
                fGridItemSetx("",iGrid,iC);
            }
        }
        if (lText.size()>iColo) iColo=lText.size();
    }
    oFile.close();

    if (bStop) return;

    gRowsMaxi=griText->rowCount()-1;
    objRowsNumb.valu=iColo;
    fRowsChck();
    if (!gConf) {fRowsNumb();fRowsFontChan();}
    fGridInit();
    fGridTitle();
    fGridShow(true);
    fSettEnab();
    fManuInit();
}
int winMain::fFileSize(QString sFile)
{
    int iSize=0;
    QByteArray aLine;
    QFile oFile;
    oFile.setFileName(sFile);
    oFile.open(QIODevice::ReadOnly|QIODevice::Text);
    while (!oFile.atEnd()) {aLine=oFile.readLine(0);iSize++;}
    oFile.close();
    return iSize;
}
void winMain::fFileEncoding(QString sFile)
{
    int i,j,k;
    char ch='\0';
    QString sT="";
    QFile oFile(sFile);
    oFile.open(QIODevice::ReadOnly|QIODevice::Text);
    gFileEnco=true;
    i=j=k=0;
    while (!oFile.atEnd())
    {
        oFile.getChar(&ch);i++;k=int(ch);
        if ((k==-17&&i==1)||k==-61||k==-100||(j==239&&k==187)||(j==128&&k==153)) {gFileEnco=false;break;}
        j=k;
    }
    oFile.close();
}
QString winMain::fFileLineForm(QString sLine)
{
    static bool bB=false;
    static bool bI=false;
    static bool bU=false;
    bool bD=false;
    sLine=sLine.trimmed();
    sLine.replace(QChar(9)," ");
    sLine.replace("  "," ");
    sLine.replace(" .",".");
    sLine.replace(" :",":");
    sLine.replace(" ;",";");
    sLine.replace(" ,",",");
    sLine.replace(" !","!");
    sLine.replace(" ?","?");
    sLine.replace("( ","(");
    sLine.replace(" )",")");
    sLine.replace("[ ","[");
    sLine.replace(" ]","]");
    sLine.replace("{ ","{");
    sLine.replace(" }","}");
    sLine.replace("<<","<");
    sLine.replace(">>",">");
    if (sLine.indexOf("<b>")!=-1 && sLine.indexOf("</b>")==-1) {sLine.append("</b>");bD=true;bB=true;}
    if (sLine.indexOf("</b>")!=-1 && sLine.indexOf("<b>")==-1) {sLine.prepend("<b>");bD=true;bB=false;}
    if (sLine.indexOf("<i>")!=-1 && sLine.indexOf("</i>")==-1) {sLine.append("</i>");bD=true;bI=true;}
    if (sLine.indexOf("</i>")!=-1 && sLine.indexOf("<i>")==-1) {sLine.prepend("<i>");bD=true;bI=false;}
    if (sLine.indexOf("<u>")!=-1 && sLine.indexOf("</u>")==-1) {sLine.append("</u>");bD=true;bU=true;}
    if (sLine.indexOf("</u>")!=-1 && sLine.indexOf("<u>")==-1) {sLine.prepend("<u>");bD=true;bU=false;}
    if (!bD)
    {
        if (bB) {sLine.prepend("<b>");sLine.append("</b>");}
        if (bI) {sLine.prepend("<i>");sLine.append("</i>");}
        if (bU) {sLine.prepend("<u>");sLine.append("</u>");}
    }
    return sLine;
}

bool winMain::fFileTextMaxi(int iGrid,int iLeng,int iChar,int iRows,int iLine,int iC)
{
    if (iGrid<0)
    {
        for (iC=0; iC<4; iC++){gFileMaxiColu[iC]=0;}
        for (int iM=0; iM<9; iM++)
        {
            gFileMaxiGrid[iM]=0;
            gFileMaxiLeng[iM]=0;
            gFileMaxiChar[iM]=0;
            gFileMaxiRows[iM]=0;
            gFileMaxiColo[iM]=0;
            gFileMaxiLine[iM]=0;
        }
    }
    else
    {
        if (iLeng>objWind.basW)
        {
            gFileErro+=QString("|%1 - text too wide").arg(iLine);
            messSkin cM;
            if (!cM.fMess(this,fraMenu,fL("FileProbWideMess").arg(iLine),fL("butYeYe"),fL("butNoNo"))) return true;
        }
        if (iGrid>gFileMaxiColu[iC-3])
        {
            gFileMaxiColu[iC-3]=iGrid;
        }
        for (int iM=0; iM<9; iM++)
        {
            if (iLeng==gFileMaxiLeng[iM]) break;
            if (iLeng>gFileMaxiLeng[iM])
            {
                for (int iN=8; iN>=iM; iN--)
                {
                    gFileMaxiGrid[iN]=gFileMaxiGrid[iN-1];
                    gFileMaxiLeng[iN]=gFileMaxiLeng[iN-1];
                    gFileMaxiChar[iN]=gFileMaxiChar[iN-1];
                    gFileMaxiRows[iN]=gFileMaxiRows[iN-1];
                    gFileMaxiColo[iN]=gFileMaxiColo[iN-1];
                    gFileMaxiLine[iN]=gFileMaxiLine[iN-1];
                }
                gFileMaxiGrid[iM]=iGrid;
                gFileMaxiLeng[iM]=iLeng;
                gFileMaxiChar[iM]=iChar;
                gFileMaxiRows[iM]=iRows;
                gFileMaxiColo[iM]=iC;
                gFileMaxiLine[iM]=iLine;
                break;
            }
        }
    }
    return false;
}
void winMain::fFileWrit(QString sFile)
{
    oFile.setFileName(sFile);
    if (!oFile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

    gGridSave=false;

    QTableWidgetItem *it1;
    QTableWidgetItem *it2;
    QString sLine;
    QString st1;
    QString st2;

    for (int r=1; r<gRowsMaxi; r++)
    {
        sLine="";
        it1=griText->item(r,3);
        it2=griText->item(r,4);
        st1=it1->text();
        st2=it2->text();
        if (gSecoText && st1.isEmpty())
        {
            st1=st2;
            st2="";
        }
        sLine=st1;
        if (objRowsNumb.valu>1)
        {
            if (!st2.isEmpty()) sLine=sLine+"\\"+st2;
        }
        if (objRowsNumb.valu>2)
        {
            QTableWidgetItem *it3=griText->item(r,5);
            QString st3=it3->text();
            if (!st3.isEmpty()) sLine=sLine+"\\"+st3;
        }
        if (objRowsNumb.valu>3)
        {
            QTableWidgetItem *it4=griText->item(r,6);
            QString st4=it4->text();
            if (!st4.isEmpty()) sLine=sLine+"\\"+st4;
        }
        sLine=sLine+"\n";
        oFile.write(sLine.toAscii());
    }
    oFile.close();
}
void winMain::fFileWritSrtx(QString sFile)
{
    oFile.setFileName(sFile);
    if (!oFile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

    gGridSave=false;

    QString sLine;
    QString sNumb;
    QString sStar;
    QString sStop;
    QString sTex1;
    QString sTex2;
    int iR;

    for (iR=1; iR<gRowsMaxi; iR++)
    {
        sNumb=griText->verticalHeaderItem(iR)->text();
        sStar=griText->item(iR,1)->text();
        sStop=griText->item(iR,2)->text();
        sTex1=griText->item(iR,3)->text();
        sTex2=griText->item(iR,4)->text();
        if (gSecoText && sTex1.isEmpty())
        {
            sTex1=sTex2;
            sTex2="";
        }
        sLine=sNumb+"\n";
        sLine+=(sStar+" --> "+sStop+"\n");
        if (!sTex1.isEmpty()) sLine+=(sTex1+"\n");
        if (!sTex2.isEmpty()) sLine+=(sTex2+"\n");
        sLine+="\n";
        oFile.write(sLine.toAscii());
    }
    oFile.close();
}
void winMain::fFileLogx()
{
    int iR;
    int iRmaxi=griText->rowCount()-1;
    int iC;
    int r;
    QString sLine;

    if (!gFileErro.isEmpty())
    {
        QStringList lProb=gFileErro.split(QString("|"));

        for (int iP=1; iP<lProb.count(); iP++)
        {
            sLine=QString("[Error] line %1\n").arg(lProb[iP]);
            if (!fFlogOpen()) return;
            oFlog.write(sLine.toAscii());
        }
    }

    for (iR=0; iR<iRmaxi; iR++)
    {
        if (griText->item(iR,0)->text()=="I")
        {
            sLine=QString("[Marked] Row %1 Col 1 : ").arg(griText->verticalHeaderItem(iR)->text().toInt());
            sLine+=QString("Text ["+griText->item(iR,3)->text()+"...]\n");
            if (!fFlogOpen()) return;
            oFlog.write(sLine.toAscii());
        }
        if (griText->item(iR,0)->text()=="E")
        {
            for (r=1; r<=gGridModi; r++)
            {
                if (iR==gEditTextRows[r])
                {
                    iC=gEditTextColu[r];
                    if (!gSrtx) iC-=2;

                    sLine=QString("[Edited] Row %1 Col %2 : ").arg(gEditTextLine[r]).arg(iC);
                    sLine+=QString("Old ["+gEditTextOldx[r]+"]");
                    sLine+=QString(" -> New ["+gEditTextNewx[r]+"]\n");
                    if (!fFlogOpen()) return;
                    oFlog.write(sLine.toAscii());
                }
            }
        }
    }
    if (oFlog.isOpen()) oFlog.close();
}
bool winMain::fFlogOpen()
{
    if (oFlog.isOpen()) return true;
    int iSize=gFile.size();
    QString sFlog=gFile.mid(0,iSize-4)+QString(".log");
    oFlog.setFileName(sFlog);
    return oFlog.open(QIODevice::WriteOnly|QIODevice::Text);
}
void winMain::fFileReadSrtx()
{
    QString sLine;
    int iGrid=0;
    int iLine=0;
    int iRows=0;
    int iColo=0;
    QStringList lText;
    int iStru=1;
    QString sNumb="";
    QString sStar="";
    QString sStop="";
    QString sTex1="",sGri1="";
    QString sTex2="",sGri2="";
    QString sTex3="",sGri3="";
    QString sTex4="",sGri4="";
    bool bOk=true;
    bool bStop=false;

    oFile.setFileName(gFile);

    if (!oFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        messSkin cM;
        cM.fMess(this,fraMenu,fL("FileProbWarnMess")+QString("|%1|%2").arg(gFile).arg(oFile.errorString()),fL("butOkOk"),"");
        return;
    }

    fFileEncoding(gFile);

    QProgressBar barFile(winWind);
    barFile.setGeometry(fraMenu->iX,fCalcPosY(21,fraMenu),fraMenu->iW,20);
    barFile.setRange(0,fFileSize(gFile));
    barFile.show();

    gWork=true;
    gManu=false;
    gAuto=true;
    gGridModi=0;
    gGridSave=false;
    fGridSaveIcon();
    gGridMark=0;
    fGridShow(false);
    fGridZero();
    gFileErro="";
    gSrtxStop="";

    fFileTextMaxi(-1,0,0,0,0,0);

    QFontMetrics mGrid=QFontMetrics(gGridFont);
    QFontMetrics mRows=QFontMetrics(gRowsFont);

    QTextStream oStrm(&oFile);
    if (gFileEnco) oStrm.setCodec("ISO-8859-1");
    else oStrm.setCodec("UTF-8");

    while (!oStrm.atEnd() && !bStop)
    {
        barFile.setValue(++iRows);

        if (iStru==1 && !sNumb.isEmpty())
        {
            griText->insertRow(++iGrid);
            fGridItemSetx("",iGrid,0);
            fGridItemSetx(sStar,iGrid,1);
            fGridItemSetx(sStop,iGrid,2);
            fGridItemSetx(sTex1,iGrid,3);
            fGridItemSetx(sTex2,iGrid,4);
            fGridItemSetx(sTex3,iGrid,5);
            fGridItemSetx(sTex4,iGrid,6);

            sGri1=sTex1;sTex1=fGridTextClean(sTex1);
            sGri2=sTex2;sTex2=fGridTextClean(sTex2);
            sGri3=sTex3;sTex3=fGridTextClean(sTex3);
            sGri4=sTex4;sTex4=fGridTextClean(sTex4);

            bStop=fFileTextMaxi(mGrid.width(sGri1),mRows.width(sTex1),sTex1.length(),iGrid,iLine,3);
            if (bStop) break;
            bStop=fFileTextMaxi(mGrid.width(sGri2),mRows.width(sTex2),sTex2.length(),iGrid,iLine,4);
            if (bStop) break;
            bStop=fFileTextMaxi(mGrid.width(sGri3),mRows.width(sTex3),sTex3.length(),iGrid,iLine,5);
            if (bStop) break;
            bStop=fFileTextMaxi(mGrid.width(sGri4),mRows.width(sTex4),sTex4.length(),iGrid,iLine,6);
            if (bStop) break;

            sNumb=sStar=sStop=sTex1=sTex2=sTex3=sTex4="";
        }

        sLine=oStrm.readLine(0).trimmed();

        if (iStru==1)
        {
            iLine=fFileSrtxVeriNumb(iRows,sLine,iLine);
            if (iLine<0) {bOk=false;break;}
            sNumb=sLine;
            iStru++;
        }
        else if (iStru==2)
        {
            if (!fFileSrtxVeriHour(iRows,sLine,iLine)) {bOk=false;break;}
            lText=sLine.split(QString(" --> "));
            sStar=lText[0];
            sStop=lText[1];
            iStru++;
        }
        else if (iStru==3)
        {
            if (sLine.length()<1) iStru=1;              // line 1 could be optional
            else
            {
                sLine=fFileLineForm(sLine);
                fFileSrtxVeriText(iRows,sLine,iLine);
                if (iColo<1) iColo=1;
                iStru++;
            }
            sTex1=sLine;
        }
        else if (iStru==4)
        {
            if (sLine.length()<1) iStru=1;              // line 2 is optional
            else
            {
                sLine=fFileLineForm(sLine);
                fFileSrtxVeriText(iRows,sLine,iLine);
                if (iColo<2) iColo=2;
                iStru++;
            }
            sTex2=sLine;
        }
        else if (iStru==5)
        {
            if (sLine.length()<1) iStru=1;              // line 3 is optional
            else
            {
                sLine=fFileLineForm(sLine);
                fFileSrtxVeriText(iRows,sLine,iLine);
                if (iColo<3) iColo=3;
                iStru++;
            }
            sTex3=sLine;
        }
        else if (iStru==6)
        {
            if (sLine.length()<1) iStru=1;              // line 4 is optional
            else
            {
                sLine=fFileLineForm(sLine);
                fFileSrtxVeriText(iRows,sLine,iLine);
                if (iColo<4) iColo=4;
                iStru++;
            }
            sTex4=sLine;
        }
        else if (iStru==7)
        {
            if (!fFileSrtxVeriBlan(iRows,sLine,iLine)) {bOk=false;break;}
            iStru=1;
        }
    }
    oFile.close();

    if (bStop) return;

    if (!sNumb.isEmpty())
    {
        griText->insertRow(++iGrid);
        fGridItemSetx("",iGrid,0);
        fGridItemSetx(sStar,iGrid,1);
        fGridItemSetx(sStop,iGrid,2);
        fGridItemSetx(sTex1,iGrid,3);
        fGridItemSetx(sTex2,iGrid,4);
        fGridItemSetx(sTex3,iGrid,5);
        fGridItemSetx(sTex4,iGrid,6);

        sTex1=fGridTextClean(sTex1);
        sTex2=fGridTextClean(sTex2);
        sTex3=fGridTextClean(sTex3);
        sTex4=fGridTextClean(sTex4);

        bStop=fFileTextMaxi(mGrid.width(sTex1),mRows.width(sTex1),sTex1.length(),iGrid,iLine,3);if (bStop) return;
        bStop=fFileTextMaxi(mGrid.width(sTex2),mRows.width(sTex2),sTex2.length(),iGrid,iLine,4);if (bStop) return;
        bStop=fFileTextMaxi(mGrid.width(sTex3),mRows.width(sTex3),sTex3.length(),iGrid,iLine,5);if (bStop) return;
        bStop=fFileTextMaxi(mGrid.width(sTex4),mRows.width(sTex4),sTex4.length(),iGrid,iLine,6);if (bStop) return;

        gSrtxStop=sStop;
    }

    gRowsMaxi=griText->rowCount()-1;
    objRowsNumb.valu=iColo;
    fRowsChck();
    if (!gConf) {fRowsNumb();fRowsFontChan();}
    fGridInit();
    fGridTitle();
    fGridShow(true);
    fSettEnab();
    fAutoInit();

    if (!bOk) {messSkin cM;cM.fMess(this,fraMenu,fL("FileProbCritMess"),fL("butOkOk"),"");}
}

int winMain::fFileSrtxVeriNumb(int iRows,QString sText,int iLine)
{
    bool bOk;

    if (sText.length()<1)
    {
        gFileErro+=QString("|%1 (file %2) - Number,unexpected empty line").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return -1;
    }
    if (!sText.at(0).isDigit())
    {
        gFileErro+=QString("|%1 (file %2) - Number,expected: %1").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return -1;
    }
    int iTemp=sText.toInt(&bOk,10);
    if (iLine==0) iLine=iTemp;
    else iLine++;
    if (iLine!=iTemp)
    {
        gFileErro+=QString("|%1 (file %2) - Number,read: %3,expected: %1").arg(iLine).arg(iRows).arg(iTemp);
        iLine=iTemp;
    }
    return iLine;
}
bool winMain::fFileSrtxVeriHour(int iRows,QString sText,int iLine)
{
    static int iPrev=0;
    bool bOk;

    if (iLine==1) iPrev=0;

    if (sText.length()<1)
    {
        gFileErro+=QString("|%1 (file %2) - Hours,unexpected empty line").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return false;
    }
    if (sText.length() != 29)
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad length (less or more than 29 char.)").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return false;
    }
    if (!sText.at(0).isDigit() || !sText.at(1).isDigit() || !sText.at(17).isDigit() || !sText.at(18).isDigit())
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad hours format").arg(iLine).arg(iRows);
        return true;
    }
    if (sText.at(2) != ':' || sText.at(19) != ':')
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad time separator,':' expected").arg(iLine).arg(iRows);
        return true;
    }
    if (!sText.at(3).isDigit() || !sText.at(4).isDigit() || !sText.at(20).isDigit() || !sText.at(21).isDigit())
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad minutes format").arg(iLine).arg(iRows);
        return true;
    }
    if (sText.at(5) != ':' || sText.at(22) != ':')
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad time separator,':' expected").arg(iLine).arg(iRows);
        return true;
    }
    if (!sText.at(6).isDigit() || !sText.at(7).isDigit() || !sText.at(23).isDigit() || !sText.at(24).isDigit())
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad seconds format").arg(iLine).arg(iRows);
        return true;
    }
    if (sText.at(8) != ',' || sText.at(25) != ',')
    {
        gFileErro+=QString("|%1 - Hours,bad time separator,',' expected").arg(iLine).arg(iRows);
        return true;
    }
    if (!sText.at(9).isDigit() || !sText.at(10).isDigit() || !sText.at(11).isDigit() || !sText.at(26).isDigit() || !sText.at(27).isDigit() || !sText.at(28).isDigit())
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad milliseconds format").arg(iLine).arg(iRows);
        return true;
    }
    if (sText.mid(12,5)!=" --> ")
    {
        gFileErro+=QString("|%1 (file %2) - Hours,bad start/end separator,' --> ' expected").arg(iLine).arg(iRows);
        return true;
    }
    QString sStar=sText.mid(0,2)+sText.mid(3,2)+sText.mid(6,2)+sText.mid(9,3);
    int iStar=sStar.toInt(&bOk,10);
    QString sStop=sText.mid(17,2)+sText.mid(20,2)+sText.mid(23,2)+sText.mid(26,3);
    int iStop=sStop.toInt(&bOk,10);
    if (iStar>=iStop)
    {
        gFileErro+=QString("|%1 (file %2) - Hours,start >= end").arg(iLine).arg(iRows);
        return true;
    }
    if (iStar<iPrev)
    {
        gFileErro+=QString("|%1 (file %2) - Hours,start %3 < previous %4").arg(iLine).arg(iRows).arg(iStar).arg(iPrev);
        return true;
    }
    iPrev=iStop;
    return true;
}
bool winMain::fFileSrtxVeriText(int iRows,QString sText,int iLine)
{
    if (sText.length()<1)
    {
        gFileErro+=QString("|%1 (file %2) - Text,unexpected empty line").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return false;
    }
    if (sText.length()>99)
    {
        gFileErro+=QString("|%1 (file %2) - Text,line length > 99 char.").arg(iLine).arg(iRows);
        return true;
    }
    for (int i=0; i<sText.length(); i++)
    {
        if (!sText.at(i).isPrint())
        {
            gFileErro+=QString("|%1 (file %2) - Text,non-printable (at %3)").arg(iLine).arg(iRows).arg(i+1);
            return true;
        }
    }
    return true;
}
bool winMain::fFileSrtxVeriBlan(int iRows,QString sText,int iLine)
{
    if (sText.length()>0)
    {
        gFileErro+=QString("|%1 (file %2) - Line break not found,empty line expected").arg(iLine).arg(iRows);
        gFileErro+=QString("|%1 (file %2) - STOPPED BEFORE FILE END").arg(iLine).arg(iRows);
        return false;
    }
    return true;
}

//=================================================================================================
// info functions
//=================================================================================================

void winMain::fFileInfoDial()
{
    if (!gGridShow || (gAuto && gPlay)) return;
    if (gInfoDial) {diaInfo->close();gInfoDial=false;return;}

    int iRmax=16;
    int iRowH=18;
    int iCol0=220;
    int iCol1=300;
    int iL=-1;
    int iWidt=(iCol0+iCol1)+14;
    int iHeig=(iRowH*iRmax)+36;
    int iLefx=diaGrid->frameGeometry().x()+diaGrid->frameGeometry().width()-iWidt-70;
    int iTopy=diaGrid->frameGeometry().y()-9;

    if (iHeig>diaGrid->iH) iHeig=diaGrid->iH;

    gInfoDial=true;

    diaInfo=new diaInfoSkin(winWind,fraMenu,fL("diaInfo"),iWidt,iHeig,iLefx,iTopy);
    connect(diaInfo,SIGNAL(sClosed()),this,SLOT(fFileInfoClos()));

    QString sStyl="QTableWidget {background-color:#222222;color:#ffffff;border:none;}";
    sStyl+="QTableCornerButton::section {background-color:#222222;color:#222222;border:none;border-bottom:1px solid #777777;}";
    sStyl+="QHeaderView {background-color:#222222;color:#222222;border:none;}";
    sStyl+="QHeaderView::section:horizontal {background-color:#222222;color:#222222;border:none;}";
    sStyl+="QHeaderView::section:vertical {font:normal 11px "+gSystFontFami+";background-color:#222222;color:#ffffff;border:1px solid #777777;border-top:0px solid #222222;}";
    sStyl+="QScrollBar:vertical {width:10px;background-color:#222222;margin:10 0 10 0;border:none;}";

    griInfo=new QTableWidget(diaInfo);
    griInfo->setGeometry(2,32,iWidt-4,iHeig-35);
    griInfo->setSelectionMode(QAbstractItemView::NoSelection);
    griInfo->setStyleSheet(sStyl);
    griInfo->horizontalHeader()->setFixedHeight(3);
    griInfo->verticalHeader()->setFixedWidth(0);
    griInfo->setColumnCount(2);
    griInfo->setColumnWidth(0,iCol0);
    griInfo->setColumnWidth(1,iCol1);
    griInfo->setRowCount(iRmax);
    connect(griInfo,SIGNAL(cellClicked(int,int)),this,SLOT(fFileInfoGoto(int,int)));

    for (int iR=0; iR<iRmax; iR++) {griInfo->setRowHeight(iR,iRowH);}

    QFileInfo fInfo=QFileInfo(gFile);

    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoName")));
    griInfo->setItem(iL,1,new QTableWidgetItem(fInfo.fileName()));
    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoPath")));
    griInfo->setItem(iL,1,new QTableWidgetItem(fInfo.absolutePath()));
    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoModi")));
    griInfo->setItem(iL,1,new QTableWidgetItem(fInfo.lastModified().toString("dd/MM/yyyy   hh:mm")));
    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoEnco")));
    griInfo->setItem(iL,1,new QTableWidgetItem(gFileEnco ? "ANSI":"UTF8"));
    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoCols")));
    griInfo->setItem(iL,1,new QTableWidgetItem(QString("%1").arg(objRowsNumb.valu)));
    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoRows")));
    griInfo->setItem(iL,1,new QTableWidgetItem(QString("%1").arg(gRowsMaxi-1)));

    if (gSrtx)
    {
        iL++;
        griInfo->insertRow(iL);
        griInfo->setRowHeight(iL,iRowH);
        griInfo->setItem(iL,0,new QTableWidgetItem(fL("GridLastItem")));
        griInfo->setItem(iL,1,new QTableWidgetItem(gSrtxStop.left(8)));
    }

    iL++;
    griInfo->setItem(iL,0,new QTableWidgetItem(fL("widInfoLine")));
    QTableWidgetItem *vl=new QTableWidgetItem(QString("%1 - %2   (%3 pix)   (%4 c.)").arg(gFileMaxiRows[0]).arg(gFileMaxiColo[0]-2).arg(gFileMaxiLeng[0]).arg(gFileMaxiChar[0]));
    vl->setIcon(QPixmap(":/Imag/QSTit_info_goto.png"));
    griInfo->setItem(iL,1,vl);

    for (int iM=1; iM<9; iM++)
    {
        if (gFileMaxiLine[iM]>0 && gFileMaxiLine[iM] != gFileMaxiLine[iM-1])
        {
            iL++;
            QTableWidgetItem *wM=new QTableWidgetItem("");
            griInfo->setItem(iL,0,wM);
            QTableWidgetItem *vM=new QTableWidgetItem(QString("%1 - %2   (%3 pix)   (%4 c.)").arg(gFileMaxiRows[iM]).arg(gFileMaxiColo[iM]-2).arg(gFileMaxiLeng[iM]).arg(gFileMaxiChar[iM]));
            vM->setIcon(QPixmap(":/Imag/QSTit_info_goto.png"));
            griInfo->setItem(iL,1,vM);
        }
    }
    if (!gFileErro.isEmpty())
    {
        QStringList lProb=gFileErro.split(QString("|"));

        iL++;
        griInfo->insertRow(iL);
        griInfo->setRowHeight(iL,iRowH);

        QTableWidgetItem *widInfoProb=new QTableWidgetItem(fL("widInfoProb"));
        widInfoProb->setBackground(gErroBack);
        widInfoProb->setForeground(gErroColo);
        griInfo->setItem(iL,0,widInfoProb);
        QTableWidgetItem *vp=new QTableWidgetItem(lProb[1]);
        vp->setIcon(QPixmap(":/Imag/QSTit_info_goto.png"));
        griInfo->setItem(iL,1,vp);

        for (int iP=2; iP<lProb.count(); iP++)
        {
            iL++;
            griInfo->insertRow(iL);
            griInfo->setRowHeight(iL,iRowH);

            QTableWidgetItem *wP=new QTableWidgetItem("");
            wP->setBackground(gErroBack);
            griInfo->setItem(iL,0,wP);
            QTableWidgetItem *vP=new QTableWidgetItem(lProb[iP]);
            vP->setIcon(QPixmap(":/Imag/QSTit_info_goto.png"));
            griInfo->setItem(iL,1,vP);
        }
    }
    diaInfo->show();
    diaInfo->setFocus();
}
void winMain::fFileInfoClos() {gInfoDial=false;}
void winMain::fFileInfoGoto(int iR,int iC)
{
    if (iC!=1) return;
    QTableWidgetItem *wc=griInfo->currentItem();
    QIcon ic=wc->icon();
    if (ic.isNull()) return;
    QString sT=wc->text();
    QStringList lT=sT.split(QString(" "));
    iR=lT[0].toInt();
    iC=lT[2].toInt();
    griText->setCurrentCell(iR,iC,QItemSelectionModel::Rows);
    griText->scrollTo(griText->currentIndex(),QAbstractItemView::PositionAtCenter);
    fGridFocus();
}

//=================================================================================================
// help functions
//=================================================================================================

void winMain::fHelpDial()
{
    if (gAuto && gPlay) return;
    if (gHelpDial) {diaHelp->close();gHelpDial=false;return;}

    gHelpDial=true;
    int iWidt=740;
    int iHeig=700;

    diaHelp=new diaSkin(winWind,fraMenu,fL("diaHelp")+" | vers. "+gVers,iWidt,iHeig,1,1);
    connect(diaHelp,SIGNAL(sClosed()),this,SLOT(fHelpDialClos()));

    texHelp=new QTextEdit("",diaHelp);
    texHelp->setStyleSheet("QTextEdit {border:none;padding:5px;} QScrollBar:vertical {width:10px;background-color:#252525;margin:10 0 10 0;border:none;}");
    texHelp->setGeometry(3,31,iWidt-5,iHeig-33);
    texHelp->setReadOnly(true);
    texHelp->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    texHelp->setFrameShape(QFrame::NoFrame);
    texHelp->setContentsMargins(1,0,1,0);
    texHelp->setFont(gRowsFont);
    texHelp->setWordWrapMode(QTextOption::WordWrap);
    texHelp->document()->setDocumentMargin(0);
    texHelp->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    texHelp->setHtml(fHelpFileRead());

    diaHelp->show();
    diaHelp->setFocus();
}
void winMain::fHelpDialClos(){gHelpDial=false;}
QString winMain::fHelpFileRead()
{
    QString sFile=":/Help/QSTit_Help_En.htm";
    if (gLang==1)
    {
        oHelp.setFileName("./QSTit_Help.htm");
        if (oHelp.open(QIODevice::ReadOnly|QIODevice::Text)) {sFile=oHelp.fileName();oHelp.close();}
    }
    oHelp.setFileName(sFile);
    oHelp.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray sHelp=oHelp.readAll();
    oHelp.close();

    QTextCodec *codec;
    codec=QTextCodec::codecForName("UTF-8");
    return codec->toUnicode(sHelp);
}

//=================================================================================================
// language functions
//=================================================================================================

void winMain::fLangFileRead()
{
    QString sFile=":/Help/QSTit_Lang_En.txt";
    QString sLine;

    if (gLang==1) sFile="./QSTit_Lang.txt";

    oLang.setFileName(sFile);
    if (!oLang.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        messSkin cM;cM.fMess(this,fraMenu,fL("FileProbWarnMess")+QString("|%1|%2").arg(sFile).arg(oLang.errorString()),fL("butOkOk"),"");
        return;
    }

    sLine=QString::fromUtf8(oLang.readLine());
    sLine = sLine.trimmed().replace("\n", "");
    sLine=sLine.mid(0,19).trimmed();
    sLine=sLine.mid(1,sLine.size()-2);
    if (gLang==1) radLangOthe->setText(sLine);

    gLangCode.clear();
    gLangText.clear();

    while (!oLang.atEnd())
    {
        sLine=QString::fromUtf8(oLang.readLine());
        sLine = sLine.trimmed().replace("\n", "");
        if(!sLine.isEmpty()) {gLangCode+=sLine.mid(0,19).trimmed();gLangText+=sLine.mid(20,99).trimmed();}
    }
    oLang.close();
}
QString winMain::fL(QString sI) {int i=gLangCode.indexOf(sI,0);if (i>-1) sI=gLangText.at(i);return sI;}
void winMain::fLAll()
{
    if (radLangOthe->isChecked()) gLang=1;else gLang=0;
    fLangFileRead();
    butExit->setText(fL("butExit"));
    butFile->setText(fL("butFile"));
    butFont->setText(fL("butFont"));
    butGridClea->setText(fL("butGridClea"));
    butGridEdit->setText(fL("butGridEdit"));
    butGridFind->setText(fL("butGridFind"));
    butGridGoto->setText(fL("butGridGoto"));
    butGridInfo->setText(fL("butGridInfo"));
    butGridLink->setText(fL("butLink"));
    butGridSave->setText(fL("butGridSave"));
    butGridUndo->setText(fL("butGridUndo"));
    butHelp->setText(fL("butHelp"));
    butHoriCent->setText(fL("butHoriCent"));
    butHoriLeft->setText(fL("butHoriLeft"));
    butHoriRigh->setText(fL("butHoriRigh"));
    butLocaCent->setText(fL("butLocaCent"));
    butLocaDown->setText(fL("butLocaDown"));
    butLocaLeft->setText(fL("butLocaLeft"));
    butLocaRigh->setText(fL("butLocaRigh"));
    butLocaUpup->setText(fL("butLocaUpup"));
    butProjAcce->setText(fL("butProjAcce"));
    butProjBack->setText(fL("butProjBack"));
    butProjDece->setText(fL("butProjDece"));
    butProjDown->setText(fL("butProjDown"));
    butProjJump->setText(fL("butProjJump"));
    butProjPlay->setText(fL("butProjPlay"));
    butProjUpup->setText(fL("butProjUpup"));
    butRoll->setText(fL("butRoll"));
    butRowsOutl->setText(fL("butRowsOutl"));
    butSett->setText(fL("butSett"));
    butSettBase->setText(fL("butSettBase"));
    butShedHoC0->setText(fL("butHoriCent"));
    butShedHoL0->setText(fL("butHoriLeft"));
    butShedHoR0->setText(fL("butHoriRigh"));
    butShedVeB0->setText(fL("butVertBott"));
    butShedVeC0->setText(fL("butVertCent"));
    butShedVeT0->setText(fL("butVertTopy"));
    butTextColo->setText(fL("butTextColo"));
    butTextBack->setText(fL("butTextBack"));
    butVertBott->setText(fL("butVertBott"));
    butVertCent->setText(fL("butVertCent"));
    butVertTopy->setText(fL("butVertTopy"));
    butWindBack->setText(fL("butWindBack"));
    chkSecoText->setText(fL("chkSecoText"));
    chkSecoItal->setText(fL("chkSecoItal"));
    diaSett->labTitl->setText(fL("diaSett"));
    labClok->setToolTip(fL("labClok"));
    labGridColo->setText(fL("labGridColo"));
    labGridFont->setText(fL("labGridFont"));
    labJumpBase->setText(fL("labJumpBase"));
    labRowsOutl->setText(fL("labRowsOutl"));
    labShedBack->setText(fL("labShedBack"));
    labShedText->setText(fL("labShedText"));
    labShedHeig->setText(fL("labShedHeig"));
    labShedHori->setText(fL("labTextAliH"));
    labShedRota->setText(fL("labShedRota"));
    labShedShow->setText(fL("labShedShow"));
    labShedSpac->setText(fL("labShedSpac"));
    labShedTit0->setText(fL("labShedTit0"));
    labShedTit1->setText(fL("labShedTit1"));
    labShedTit2->setText(fL("labShedTit2"));
    labShedTit3->setText(fL("labShedTit3"));
    labShedTit4->setText(fL("labShedTit4"));
    labShedVert->setText(fL("labTextAliV"));
    labTaskShow->setText(fL("labTaskShow"));
    labTextAliH->setText(fL("labTextAliH"));
    labTextAliV->setText(fL("labTextAliV"));
    labTextFont->setText(fL("labTextFont"));
    labTime->setToolTip(fL("labTime"));
    labWindBack->setText(fL("labWindBack"));
    labWorkLang->setText(fL("labWorkLang"));
    radGridDark->setText(fL("radGridDark"));
    radGridWhit->setText(fL("radGridWhit"));
    radSaveExiF->setText(fL("radExitSavF"));
    radSaveExiP->setText(fL("radExitSavP"));
    radTaskHide->setText(fL("radTaskHide"));
    radTaskShow->setText(fL("radTaskShow"));
    tabSett->setTabText(0,fL("tabSett0"));
    tabSett->setTabText(1,fL("tabSett1"));
    tabSett->setTabText(2,fL("tabSett2"));
    tabSett->setTabText(3,fL("tabSett3"));
    texRowsBack->setText(fL("texRowsBack"));
    texRowsDime->setText(fL("texRowsDime"));
    texRowsFram->setText(fL("texRowsFram"));
    texRowsLoca->setText(fL("texRowsLoca"));
    texRowsRota->setText(fL("texRowsRota"));
    texRowsSpac->setText(fL("texRowsSpac"));
    texRowsText->setText(fL("texRowsText"));
    if (gGridShow) fGridTitle();
    diaGrid->fWorkLang(gLangCode,gLangText);
    griText->fWorkLang(gLangCode,gLangText);
    fRowsInit();
}

//=================================================================================================
// other functions
//=================================================================================================

void winMain::fClearAll(bool bMess)
{
    if (bMess) {messSkin cM;if (!cM.fMess(this,fraMenu,fL("msgCleaAllMess"),fL("butYeYe"),fL("butNoNo"))) return;}
    if (gAuto && gPlay) fAutoPaus();
    fWindLogoHide();
    fWindClear();
    fRowsFramPosi();
    fRowsShow(1);
    fRowsClear();
    fSettClos();
    diaGrid->fRePosi();
    fGridEditEnab();
    if (gInfoDial) {diaInfo->close();gInfoDial=false;}
    if (gHelpDial) {diaHelp->close();gHelpDial=false;}
    gPlay=false;
    gInit=false;
    gAcce=0;
    gJump=0;
    labTime->setText("00:00:00");
    labPuls->setText("");
    labJump->setText("");
    if (gGridShow) griText->setCurrentCell(0,1);
}
void winMain::fClearGrid()
{
    messSkin cM;
    if (!cM.fMess(this,fraMenu,fL("msgCleaGridMess"),fL("butYeYe"),fL("butNoNo"))) return;
    if (gAuto && gPlay) fAutoPaus();
    fWindLogoHide();
    fWindClear();
    fRowsShow(1);
    fRowsClear();
    fSettClos();
    fGridEditEnab();
    if (gInfoDial) {diaInfo->close();gInfoDial=false;}
    if (gHelpDial) {diaHelp->close();gHelpDial=false;}
    gPlay=false;
    gInit=false;
    gAcce=0;
    gJump=0;
    labTime->setText("00:00:00");
    labPuls->setText("");
    labJump->setText("");
    if (gGridShow) griText->setCurrentCell(0,1);
}

void winMain::keyPressEvent(QKeyEvent *qe)
{
    if (qe->modifiers()==Qt::NoModifier)
    {
        switch (qe->key())
        {
            case Qt::Key_N:         {fRowsShow(-1);break;}
            case Qt::Key_P:         {fAutoAcce();break;}
            case Qt::Key_Plus:      {fAutoAcce();break;}
            case Qt::Key_M:         {fAutoDece();break;}
            case Qt::Key_Minus:     {fAutoDece();break;}
            case Qt::Key_F1:        {fHelpDial();break;}
            case Qt::Key_PageUp:    {fRowsLocU();break;}
            case Qt::Key_PageDown:  {fRowsLocD();break;}
            case Qt::Key_Home:      {fRowsLocL();break;}
            case Qt::Key_End:       {fRowsLocR();break;}
            case Qt::Key_Up:        {fButtPrev();break;}
            case Qt::Key_Down:      {fButtNext();break;}
            case Qt::Key_Left:      {fAutoBack();break;}
            case Qt::Key_Right:     {fAutoJump();break;}
            case Qt::Key_Space:     {gAuto ? fAutoStar():fButtNext();break;}
            default: {QWidget::keyPressEvent(qe);}
        }
    }
    else if (qe->modifiers()==Qt::ShiftModifier)
    {
        switch (qe->key())
        {
            case Qt::Key_Plus:      {fAutoAcce();break;}
            case Qt::Key_PageUp:    {fRowsLocUFast();break;}
            case Qt::Key_PageDown:  {fRowsLocDFast();break;}
            case Qt::Key_Home:      {fRowsLocLFast();break;}
            case Qt::Key_End:       {fRowsLocRFast();break;}
            default: {QWidget::keyPressEvent(qe);}
        }
    }
    else if (qe->modifiers()==Qt::ControlModifier)
    {
        switch (qe->key())
        {
            case Qt::Key_Q:         {fWindExitDial();break;}
            case Qt::Key_O:         {fFileDial();break;}
            case Qt::Key_S:         {fSettShow();break;}
            case Qt::Key_R:         {fClearGrid();break;}
            case Qt::Key_I:         {fFileInfoDial();break;}
            case Qt::Key_E:         {fGridEditButt();break;}
            case Qt::Key_Z:         {fGridUndo();break;}
            case Qt::Key_Up:        {fRowsLocU();break;}
            case Qt::Key_Down:      {fRowsLocD();break;}
            case Qt::Key_Left:      {fRowsLocL();break;}
            case Qt::Key_Right:     {fRowsLocR();break;}
            default: {QWidget::keyPressEvent(qe);}
        }
    }
    else if (qe->modifiers()==Qt::KeypadModifier)
    {
        switch (qe->key())
        {
            case Qt::Key_Plus:      {fAutoAcce();break;}
            case Qt::Key_Minus:     {fAutoDece();break;}
            case Qt::Key_Period:    {fRowsShow(-1);break;}
            case Qt::Key_9:         {fRowsLocU();break;}
            case Qt::Key_3:         {fRowsLocD();break;}
            case Qt::Key_7:         {fRowsLocL();break;}
            case Qt::Key_1:         {fRowsLocR();break;}
            case Qt::Key_8:         {fButtPrev();break;}
            case Qt::Key_2:         {fButtNext();break;}
            case Qt::Key_4:         {fAutoBack();break;}
            case Qt::Key_6:         {fAutoJump();break;}
            case Qt::Key_0:         {gAuto ? fAutoStar():fButtNext();break;}
            case Qt::Key_Delete:    {fRowsShow(-1);break;}
            case Qt::Key_Insert:    {gAuto ? fAutoStar():fButtNext();break;}
            case Qt::Key_PageUp:    {fRowsLocU();break;}
            case Qt::Key_PageDown:  {fRowsLocD();break;}
            case Qt::Key_Home:      {fRowsLocL();break;}
            case Qt::Key_End:       {fRowsLocR();break;}
            case Qt::Key_Up:        {fButtPrev();break;}
            case Qt::Key_Down:      {fButtNext();break;}
            case Qt::Key_Left:      {fAutoBack();break;}
            case Qt::Key_Right:     {fAutoJump();break;}
            case Qt::Key_Slash:     {if (gGridShow) fGridMarkRows(griText->currentRow());break;}
            default: {QWidget::keyPressEvent(qe);}
        }
    }
    else
    {
        switch (qe->key())
        {
            case Qt::Key_Return:    {break;}
            case Qt::Key_Enter:     {break;}
            case Qt::Key_Tab:       {break;}
            default: {QWidget::keyPressEvent(qe);}
        }
    }
}

void winMain::fConfConf(QString sVari,QString sValu)
{
    bool ok;
    int iV=sValu.toInt(&ok,10);
    bool bV=sValu=="true" ? true:false;
    QString sV=sValu;

    if (sVari=="test")
    {
        QMessageBox::information(this,"test",QString("objRow1.spac %1, objRow2.spac %2").arg(objRow1.spac).arg(objRow2.spac));return;
    }
    if (sVari=="Lang")
    {
        if (iV<0 || iV>1) iV=0;gLang=iV;
        if (gLang==0) radLangEngl->setChecked(true);
        else radLangOthe->setChecked(true);
        return;
    }
    if (sVari=="MenuLink")
    {
        diaGrid->bLink=bV;
        if (bV) butGridLink->setIcon(QPixmap(":/Imag/QSTit_link_none.png"));
        else butGridLink->setIcon(QPixmap(":/Imag/QSTit_link_done.png"));
        return;
    }
    if (sVari=="Menu-X")        {fraMenu->iX=iV;return;}
    if (sVari=="Menu-Y")        {fraMenu->iY=iV;return;}
    if (sVari=="Menu-W")        {fraMenu->iW=iV;return;}
    if (sVari=="Menu-H")        {fraMenu->iH=iV;return;}
    if (sVari=="RowsNumb")      {if (iV<objRowsNumb.mini || iV>objRowsNumb.maxi) iV=objRowsNumb.val0;objRowsNumb.valu=iV;return;}
    if (sVari=="RowsSpac")      {if (iV<objRowsSpac.mini || iV>objRowsSpac.maxi) iV=objRowsSpac.val0;objRowsSpac.valu=iV;return;}
    if (sVari=="RowsHone")      {if (iV<objRowsHeig.mini || iV>objRowsHeig.maxi) iV=objRowsHeig.val0;objRowsHeig.valu=iV;return;}
    if (sVari=="Rows-X")        {fraRows->iX=iV;return;}
    if (sVari=="Rows-Y")        {fraRows->iY=iV;return;}
    if (sVari=="Rows-W")        {fraRows->iW=iV;return;}
    if (sVari=="Rows-H")        {fraRows->iH=iV;return;}

    if (sVari=="Row1Show")      {objRow1.show=bV;radShedSho1->setChecked(bV);return;}
    if (sVari=="Row1Spac")      {if (iV<objRowsSpac.mini || iV>objRowsSpac.maxi) iV=objRowsSpac.val0;objRow1.spac=iV;return;}
    if (sVari=="Row1Heig")      {if (iV<objRowsHeig.mini || iV>objRowsHeig.maxi) iV=objRowsHeig.val0;objRow1.heig=iV;objRow1.savH=iV;return;}
    if (sVari=="Row1Widt")      {if (iV<objRowsWidt.mini || iV>objRowsWidt.maxi) iV=objRowsWidt.val0;objRow1.widt=iV;return;}
    if (sVari=="Row1FontName")  {objRow1.font.setFamily(sV);return;}
    if (sVari=="Row1FontSize")  {objRow1.font.setPointSize(iV);return;}
    if (sVari=="Row1FontWeig")  {objRow1.font.setWeight(iV);return;}
    if (sVari=="Row1FontItal")  {objRow1.font.setItalic(bV);return;}
    if (sVari=="Row1TextColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#ffffff";objRow1.colF=sV;return;}
    if (sVari=="Row1BackColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#000000";objRow1.colB=sV;return;}
    if (sVari=="Row1-X")        {objRow1.x=iV;return;}
    if (sVari=="Row1-Y")        {objRow1.y=iV;return;}
    if (sVari=="Row1Rota")      {objRow1.rota=iV;return;}
    if (sVari=="Row1Hori")      {objRow1.hori=iV;return;}
    if (sVari=="Row1Vert")      {objRow1.vert=iV;return;}
    if (sVari=="Row1Outl")      {objRow1.outl=iV;return;}

    if (sVari=="Row2Show")      {objRow2.show=bV;radShedSho2->setChecked(bV);return;}
    if (sVari=="Row2Spac")      {if (iV<objRowsSpac.mini || iV>objRowsSpac.maxi) iV=objRowsSpac.val0;objRow2.spac=iV;return;}
    if (sVari=="Row2Heig")      {if (iV<objRowsHeig.mini || iV>objRowsHeig.maxi) iV=objRowsHeig.val0;objRow2.heig=iV;objRow2.savH=iV;return;}
    if (sVari=="Row2Widt")      {if (iV<objRowsWidt.mini || iV>objRowsWidt.maxi) iV=objRowsWidt.val0;objRow2.widt=iV;return;}
    if (sVari=="Row2FontName")  {objRow2.font.setFamily(sValu);return;}
    if (sVari=="Row2FontSize")  {objRow2.font.setPointSize(iV);return;}
    if (sVari=="Row2FontWeig")  {objRow2.font.setWeight(iV);return;}
    if (sVari=="Row2FontItal")  {objRow2.font.setItalic(bV);return;}
    if (sVari=="Row2TextColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#ffffff";objRow2.colF=sV;return;}
    if (sVari=="Row2BackColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#000000";objRow2.colB=sV;return;}
    if (sVari=="Row2-X")        {objRow2.x=iV;return;}
    if (sVari=="Row2-Y")        {objRow2.y=iV;return;}
    if (sVari=="Row2Rota")      {objRow2.rota=iV;return;}
    if (sVari=="Row2Hori")      {objRow2.hori=iV;return;}
    if (sVari=="Row2Vert")      {objRow2.vert=iV;return;}
    if (sVari=="Row2Outl")      {objRow2.outl=iV;return;}

    if (sVari=="Row3Show")      {objRow3.show=bV;radShedSho3->setChecked(bV);return;}
    if (sVari=="Row3Spac")      {if (iV<objRowsSpac.mini || iV>objRowsSpac.maxi) iV=objRowsSpac.val0;objRow3.spac=iV;return;}
    if (sVari=="Row3Heig")      {if (iV<objRowsHeig.mini || iV>objRowsHeig.maxi) iV=objRowsHeig.val0;objRow3.heig=iV;objRow3.savH=iV;return;}
    if (sVari=="Row3Widt")      {if (iV<objRowsWidt.mini || iV>objRowsWidt.maxi) iV=objRowsWidt.val0;objRow3.widt=iV;return;}
    if (sVari=="Row3FontName")  {objRow3.font.setFamily(sValu);return;}
    if (sVari=="Row3FontSize")  {objRow3.font.setPointSize(iV);return;}
    if (sVari=="Row3FontWeig")  {objRow3.font.setWeight(iV);return;}
    if (sVari=="Row3FontItal")  {objRow3.font.setItalic(bV);return;}
    if (sVari=="Row3TextColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#ffffff";objRow3.colF=sV;return;}
    if (sVari=="Row3BackColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#000000";objRow3.colB=sV;return;}
    if (sVari=="Row3-X")        {objRow3.x=iV;return;}
    if (sVari=="Row3-Y")        {objRow3.y=iV;return;}
    if (sVari=="Row3Rota")      {objRow3.rota=iV;return;}
    if (sVari=="Row3Hori")      {objRow3.hori=iV;return;}
    if (sVari=="Row3Vert")      {objRow3.vert=iV;return;}
    if (sVari=="Row3Outl")      {objRow3.outl=iV;return;}

    if (sVari=="Row4Show")      {objRow4.show=bV;radShedSho4->setChecked(bV);return;}
    if (sVari=="Row4Heig")      {if (iV<objRowsHeig.mini || iV>objRowsHeig.maxi) iV=objRowsHeig.val0;objRow4.heig=iV;objRow4.savH=iV;return;}
    if (sVari=="Row4Widt")      {if (iV<objRowsWidt.mini || iV>objRowsWidt.maxi) iV=objRowsWidt.val0;objRow4.widt=iV;return;}
    if (sVari=="Row4FontName")  {objRow4.font.setFamily(sValu);return;}
    if (sVari=="Row4FontSize")  {objRow4.font.setPointSize(iV);return;}
    if (sVari=="Row4FontWeig")  {objRow4.font.setWeight(iV);return;}
    if (sVari=="Row4FontItal")  {objRow4.font.setItalic(bV);return;}
    if (sVari=="Row4TextColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#ffffff";objRow4.colF=sV;return;}
    if (sVari=="Row4BackColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#000000";objRow4.colB=sV;return;}
    if (sVari=="Row4-X")        {objRow4.x=iV;return;}
    if (sVari=="Row4-Y")        {objRow4.y=iV;return;}
    if (sVari=="Row4Rota")      {objRow4.rota=iV;return;}
    if (sVari=="Row4Hori")      {objRow4.hori=iV;return;}
    if (sVari=="Row4Vert")      {objRow4.vert=iV;return;}
    if (sVari=="Row4Outl")      {objRow4.outl=iV;return;}

    if (sVari=="Grid-X")        {diaGrid->iX=iV;return;}
    if (sVari=="Grid-Y")        {diaGrid->iY=iV;return;}
    if (sVari=="Grid-W")        {diaGrid->iW=iV;return;}
    if (sVari=="Grid-H")        {diaGrid->iH=iV;return;}
    if (sVari=="GridFontFami")  {gGridFont.setFamily(sValu);return;}
    if (sVari=="GridFontSize")  {gGridFont.setPointSize(iV);return;}
    if (sVari=="TextOutlColo")  {if (sV.length() != 7 || !sV.startsWith("#")) sV="#7f7f7f";gOutlColo=QColor(sV);return;}
    if (sVari=="TextSecoText")  {gSecoText=sValu=="true" ? true:false;if (gSecoText) chkSecoText->setChecked(true);return;}
    if (sVari=="TextSecoItal")  {gSecoItal=sValu=="true" ? true:false;if (gSecoItal) chkSecoItal->setChecked(true);return;}
    if (sVari=="JumpBase")      {gJumpBase=iV;spiJumpBase->setValue(gJumpBase/100);return;}
}
void winMain::fConfRead()
{
    QString sLine;
    QStringList lText;
    QStringList lValu;
    QString sVari;
    QString sValu;

    oConf.setFileName(gConfFile);
    if (!oConf.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    while (!oConf.atEnd())
    {
        sLine=fFileLineForm(QString::fromUtf8(oConf.readLine()));
        if(!sLine.isEmpty())
        {
            lText=sLine.split(QString("="));
            sVari=lText[0].trimmed();
            lValu=lText[1].split(QString("'"));
            sValu=lValu[0].trimmed();
            fConfConf(sVari,sValu);
        }
    }
    oConf.close();
    if (gLang==1) fLAll();
    fRowsFramCent();
    gRowsHcenPrev=gRowsHcen;
    gRowsVcenPrev=gRowsVcen;
    fRowsAdapt();
    diaGrid->setGeometry(diaGrid->iX,diaGrid->iY,diaGrid->iW,diaGrid->iH);
}
void winMain::fConfWrit(int pT)
{
    QString sConf="";
    int iSize=gFile.size();
    QString sText="";

    if (pT==1) sConf=gConfFile;
    if (pT==2) sConf=gFile.mid(0,iSize-4)+QString(".cfg");

    oConf.setFileName(sConf);
    if (!oConf.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    sText+=fConfWritLine(QString("Grid-H=%1").arg(diaGrid->iH),                                 "grid frame height");
    sText+=fConfWritLine(QString("Grid-W=%1").arg(diaGrid->iW),                                 "grid frame width");
    sText+=fConfWritLine(QString("Grid-X=%1").arg(diaGrid->iX),                                 "grid frame left");
    sText+=fConfWritLine(QString("Grid-Y=%1").arg(diaGrid->iY),                                 "grid frame top");
    sText+=fConfWritLine(QString("GridFontFami=%1").arg(gGridFont.family()),                    "grid font");
    sText+=fConfWritLine(QString("GridFontSize=%1").arg(gGridFont.pointSize()),                 "grid font size");
    sText+=fConfWritLine(QString("JumpBase=%1").arg(gJumpBase),                                 "jump base (1/10 sec.)");
    sText+=fConfWritLine(QString("Lang=%1").arg(gLang),                                         "0=english,1=other (from QSTit_Lang.txt)");
    sText+=fConfWritLine(QString("MenuLink=%1").arg(diaGrid->bLink ? "true":"false"),           "menu linked to grid");
    sText+=fConfWritLine(QString("Menu-X=%1").arg(fraMenu->iX),                                 "menu left");
    sText+=fConfWritLine(QString("Menu-Y=%1").arg(fraMenu->iY),                                 "menu top");
    sText+=fConfWritLine(QString("Menu-W=%1").arg(fraMenu->iW),                                 "menu width");
    sText+=fConfWritLine(QString("Menu-H=%1").arg(fraMenu->iH),                                 "menu height");
    sText+=fConfWritLine(QString("Row1BackColo=%1").arg(objRow1.colB.name()),                   "row1 backcolor");
    sText+=fConfWritLine(QString("Row1FontItal=%1").arg(objRow1.font.italic() ? "true":"false"),"     font italic");
    sText+=fConfWritLine(QString("Row1FontName=%1").arg(objRow1.font.family()),                 "     font");
    sText+=fConfWritLine(QString("Row1FontSize=%1").arg(objRow1.font.pointSize()),              "     font size");
    sText+=fConfWritLine(QString("Row1FontWeig=%1").arg(objRow1.font.weight()),                 "     font weight");
    sText+=fConfWritLine(QString("Row1Heig=%1").arg(objRow1.heig),                              "     height");
    sText+=fConfWritLine(QString("Row1Hori=%1").arg(objRow1.hori),                              "     alignment hori. (left=-1,center=0,right=1)");
    sText+=fConfWritLine(QString("Row1Outl=%1").arg(objRow1.outl),                              "     outline thickness");
    sText+=fConfWritLine(QString("Row1Rota=%1").arg(objRow1.rota),                              "     rotation");
    sText+=fConfWritLine(QString("Row1Show=%1").arg(objRow1.show ? "true":"false"),             "     shown");
    sText+=fConfWritLine(QString("Row1Spac=%1").arg(objRow1.spac),                              "     spacing");
    sText+=fConfWritLine(QString("Row1TextColo=%1").arg(objRow1.colF.name()),                   "     text color");
    sText+=fConfWritLine(QString("Row1Vert=%1").arg(objRow1.vert),                              "     alignment vert. (top=1,center=0,bottom=-1)");
    sText+=fConfWritLine(QString("Row1Widt=%1").arg(objRow1.widt),                              "     width");
    sText+=fConfWritLine(QString("Row1-X=%1").arg(objRow1.x),                                   "     left (always 0)");
    sText+=fConfWritLine(QString("Row1-Y=%1").arg(objRow1.y),                                   "     top");
    sText+=fConfWritLine(QString("Row2BackColo=%1").arg(objRow2.colB.name()),                   "row2 backcolor");
    sText+=fConfWritLine(QString("Row2FontItal=%1").arg(objRow2.font.italic() ? "true":"false"),"     font italic");
    sText+=fConfWritLine(QString("Row2FontName=%1").arg(objRow2.font.family()),                 "     font");
    sText+=fConfWritLine(QString("Row2FontSize=%1").arg(objRow2.font.pointSize()),              "     font size");
    sText+=fConfWritLine(QString("Row2FontWeig=%1").arg(objRow2.font.weight()),                 "     font weight");
    sText+=fConfWritLine(QString("Row2Heig=%1").arg(objRow2.heig),                              "     height");
    sText+=fConfWritLine(QString("Row2Hori=%1").arg(objRow2.hori),                              "     alignment hori. (left=-1,center=0,right=1)");
    sText+=fConfWritLine(QString("Row2Outl=%1").arg(objRow2.outl),                              "     outline thickness");
    sText+=fConfWritLine(QString("Row2Rota=%1").arg(objRow2.rota),                              "     rotation");
    sText+=fConfWritLine(QString("Row2Show=%1").arg(objRow2.show ? "true":"false"),             "     shown");
    sText+=fConfWritLine(QString("Row2Spac=%1").arg(objRow2.spac),                              "     spacing");
    sText+=fConfWritLine(QString("Row2TextColo=%1").arg(objRow2.colF.name()),                   "     text color");
    sText+=fConfWritLine(QString("Row2Vert=%1").arg(objRow2.vert),                              "     alignment vert. (top=1,center=0,bottom=-1)");
    sText+=fConfWritLine(QString("Row2Widt=%1").arg(objRow2.widt),                              "     width");
    sText+=fConfWritLine(QString("Row2-X=%1").arg(objRow2.x),                                   "     left (always 0)");
    sText+=fConfWritLine(QString("Row2-Y=%1").arg(objRow2.y),                                   "     top");
    sText+=fConfWritLine(QString("Row3BackColo=%1").arg(objRow3.colB.name()),                   "row3 backcolor");
    sText+=fConfWritLine(QString("Row3FontItal=%1").arg(objRow3.font.italic() ? "true":"false"),"     font italic");
    sText+=fConfWritLine(QString("Row3FontName=%1").arg(objRow3.font.family()),                 "     font");
    sText+=fConfWritLine(QString("Row3FontSize=%1").arg(objRow3.font.pointSize()),              "     font size");
    sText+=fConfWritLine(QString("Row3FontWeig=%1").arg(objRow3.font.weight()),                 "     font weight");
    sText+=fConfWritLine(QString("Row3Heig=%1").arg(objRow3.heig),                              "     height");
    sText+=fConfWritLine(QString("Row3Hori=%1").arg(objRow3.hori),                              "     alignment hori. (left=-1,center=0,right=1)");
    sText+=fConfWritLine(QString("Row3Outl=%1").arg(objRow3.outl),                              "     outline thickness");
    sText+=fConfWritLine(QString("Row3Rota=%1").arg(objRow3.rota),                              "     rotation");
    sText+=fConfWritLine(QString("Row3Show=%1").arg(objRow3.show ? "true":"false"),             "     shown");
    sText+=fConfWritLine(QString("Row3Spac=%1").arg(objRow3.spac),                              "     spacing");
    sText+=fConfWritLine(QString("Row3TextColo=%1").arg(objRow3.colF.name()),                   "     text color");
    sText+=fConfWritLine(QString("Row3Vert=%1").arg(objRow3.vert),                              "     alignment vert. (top=1,center=0,bottom=-1)");
    sText+=fConfWritLine(QString("Row3Widt=%1").arg(objRow3.widt),                              "     width");
    sText+=fConfWritLine(QString("Row3-X=%1").arg(objRow3.x),                                   "     left (always 0)");
    sText+=fConfWritLine(QString("Row3-Y=%1").arg(objRow3.y),                                   "     top");
    sText+=fConfWritLine(QString("Row4BackColo=%1").arg(objRow4.colB.name()),                   "row4 backcolor");
    sText+=fConfWritLine(QString("Row4FontItal=%1").arg(objRow4.font.italic() ? "true":"false"),"     font italic");
    sText+=fConfWritLine(QString("Row4FontName=%1").arg(objRow4.font.family()),                 "     font");
    sText+=fConfWritLine(QString("Row4FontSize=%1").arg(objRow4.font.pointSize()),              "     font size");
    sText+=fConfWritLine(QString("Row4FontWeig=%1").arg(objRow4.font.weight()),                 "     font weight");
    sText+=fConfWritLine(QString("Row4Heig=%1").arg(objRow4.heig),                              "     height");
    sText+=fConfWritLine(QString("Row4Hori=%1").arg(objRow4.hori),                              "     alignment hori. (left=-1,center=0,right=1)");
    sText+=fConfWritLine(QString("Row4Outl=%1").arg(objRow4.outl),                              "     outline thickness");
    sText+=fConfWritLine(QString("Row4Rota=%1").arg(objRow4.rota),                              "     rotation");
    sText+=fConfWritLine(QString("Row4Show=%1").arg(objRow4.show ? "true":"false"),             "     shown");
    sText+=fConfWritLine(QString("Row4TextColo=%1").arg(objRow4.colF.name()),                   "     text color");
    sText+=fConfWritLine(QString("Row4Vert=%1").arg(objRow4.vert),                              "     alignment vert. (top=1,center=0,bottom=-1)");
    sText+=fConfWritLine(QString("Row4Widt=%1").arg(objRow4.widt),                              "     width");
    sText+=fConfWritLine(QString("Row4-X=%1").arg(objRow4.x),                                   "     left (always 0)");
    sText+=fConfWritLine(QString("Row4-Y=%1").arg(objRow4.y),                                   "     top");
    sText+=fConfWritLine(QString("RowsHone=%1").arg(objRowsHeig.valu),                          "height of one row");
    sText+=fConfWritLine(QString("RowsNumb=%1").arg(objRowsNumb.valu),                          "number of rows (min=1,max=4)");
    sText+=fConfWritLine(QString("RowsSpac=%1").arg(objRowsSpac.valu),                          "space between rows");
    sText+=fConfWritLine(QString("Rows-X=%1").arg(fraRows->iX),                                 "rows frame left");
    sText+=fConfWritLine(QString("Rows-Y=%1").arg(fraRows->iY),                                 "rows frame top");
    sText+=fConfWritLine(QString("Rows-W=%1").arg(fraRows->iW),                                 "rows frame width");
    sText+=fConfWritLine(QString("Rows-H=%1").arg(fraRows->iH),                                 "rows frame height");
    sText+=fConfWritLine(QString("TextOutlColo=%1").arg(gOutlColo.name()),                      "text outline color");
    sText+=fConfWritLine(QString("TextSecoItal=%1").arg(gSecoItal ? "true":"false"),            "Second text line in italic");
    sText+=fConfWritLine(QString("TextSecoText=%1").arg(gSecoText ? "true":"false"),            "Single text line displayed on row 2");

    oConf.write(sText.toUtf8());
    oConf.close();

    messSkin cM;cM.fMess(this,fraMenu,fL("msgConfWriteDone"),fL("butOkOk"),"");
}
QString winMain::fConfWritLine(QString sText,QString sComm)
{
    QString sLine=sText+QString(39,' ');
    sLine.resize(39);
    sLine+="' "+sComm+"\n";
    return sLine;
}

//=================================================================================================
// manual
//=================================================================================================

void winMain::fManuInit()
{
    gManu=true;
    gShow=true;
    gShowButt=true;
    gRows=griText->currentRow();
    fMenuAdapt(1);
    griText->setFocus();
    griText->setCurrentCell(0,1);
}
void winMain::fButtPrev()
{
    if (!gGridShow) return;
    if (gShow)
    {
        if (griText->currentRow()>0)
        {
            if (!gShowButt)
            {
                gRows=griText->currentRow()-1;
                griText->setCurrentCell(gRows,1);
                griText->scrollTo(griText->currentIndex(),QAbstractItemView::PositionAtCenter);
            }
            else
            {
                fGridRows(gRows);
            }
            fGridFocus();
            if (gAuto) fAutoTimeInit();
        }
    }
    else
    {
        fRowsClear();
    }
    gShow=!gShow;
    gShowButt=false;
}
void winMain::fButtNext()
{
    if (!gGridShow) return;
    if (gShow)
    {
        if (griText->currentRow()<gRowsMaxi)
        {
            if (gShowButt)
            {
                gRows=griText->currentRow()+1;
                griText->setCurrentCell(gRows,1);
                griText->scrollTo(griText->currentIndex(),QAbstractItemView::PositionAtCenter);
            }
            else
            {
                fGridRows(gRows);
            }
            fGridFocus();
            if (gAuto) fAutoTimeInit();
        }
    }
    else
    {
        fRowsClear();
    }
    gShow=!gShow;
    gShowButt=true;
}

//=================================================================================================
// automatic
//=================================================================================================

void winMain::fAutoInit()
{
    gAuto=true;
    gShow=true;
    gShowButt=true;
    gPlay=false;
    gInit=false;
    gRows=0;
    gAcce=0;
    gJump=0;
    fMenuAdapt(2);
    diaGrid->fRePosi();
    griText->setFocus();
    griText->setCurrentCell(0,1);
}
void winMain::fAutoPaus()
{
    fGridEditEnab();
    butProjPlay->setIcon(QPixmap(":/Imag/QSTit_play.png"));
    tmrAuto->stop();
}
void winMain::fAutoStar()
{
    gPlay=!gPlay;
    if (!gPlay) {fAutoPaus();return;}
    if (gHelpDial) {diaHelp->close();gHelpDial=false;}
    if (gInfoDial) {diaInfo->close();gInfoDial=false;}
    fGridEditDisa();
    butProjPlay->setIcon(QPixmap(":/Imag/QSTit_paus.png"));
    fRowsShow(1);
    if (!gInit)
    {
        fAutoStarInit();
        tmrAuto=new QTimer(this);
        connect(tmrAuto,SIGNAL(timeout()),this,SLOT(fAutoClok()));
        tmrAuto->start(gPuls);
        gInit=true;
    }
    else
    {
        tmrAuto->start();
    }
}
void winMain::fAutoStarInit()
{
    gRows=griText->currentRow();
    if (gRows==0){gRows=1;griText->setCurrentCell(gRows,1);}
    fAutoTimeInit();
}
void winMain::fAutoTimeInit()
{
    timAuto.setHMS(0,0,0,0);
    QString sT=griText->item(gRows,1)->text();
    if (!sT.isEmpty()) timAuto=fAutoTimeConv(sT);
    labTime->setText(timAuto.toString("hh:mm:ss"));
}
QTime winMain::fAutoTimeConv(QString sT)
{
    int iH=sT.mid(0,2).toInt();
    int iM=sT.mid(3,2).toInt();
    int iS=sT.mid(6,2).toInt();
    int iX=sT.mid(9,3).toInt();
    if (iH==99) {iH=0;iM=0;iS=0;iX=0;}
    QTime tR(iH,iM,iS,iX);
    return tR;
}
void winMain::fAutoClok()
{
    static int iJumpShow=0;
    int iBeat=gPuls+gAcce;
    double dJump=(double)gJumpBase/1000;

    timAuto=timAuto.addMSecs(iBeat+gJump);
    labTime->setText(timAuto.toString("hh:mm:ss"));
    fAutoAcceShow();
    if (gJump==0)
    {
        if (iJumpShow==0) labJump->setText("");
        else iJumpShow--;
    }
    else
    {
        if (gJump>0) {labJump->setText(QString("+%1").arg(dJump,0,'f',1));}
        else {labJump->setText(QString("-%1").arg(dJump,0,'f',1));fAutoJumpBack();}
        iJumpShow=25;
    }
    gJump=0;
    fAutoGridShow();
}
void winMain::fAutoAcceShow()
{
    int iBeat=gPuls+gAcce;
    double dBeat=(double)iBeat/(double)gPuls;
    if (dBeat==1) labPuls->setText("");
    else labPuls->setText(QString("%1").arg(dBeat,0,'f',2));
}
void winMain::fAutoJumpBack()
{
    int iPrev=gRows-1;if (iPrev<1) return;
    timStar=fAutoTimeConv(griText->item(iPrev,1)->text());
    timStop=fAutoTimeConv(griText->item(iPrev,2)->text());
    if (timAuto>=timStar  && timAuto<timStop) gRows=iPrev;
}
void winMain::fAutoGridShow()
{
    if (gRows>gRowsMaxi) {gRows=gRowsMaxi;griText->setCurrentCell(gRows,1);fRowsClear();gPlay=false;fAutoPaus();return;}
    timStop=fAutoTimeConv(griText->item(gRows,2)->text());
    if (timAuto>timStop) {fRowsClear();gRows++;return;}
    timStar=fAutoTimeConv(griText->item(gRows,1)->text());
    if (timAuto>=timStar) {griText->setCurrentCell(gRows,1);griText->scrollTo(griText->currentIndex(),QAbstractItemView::PositionAtCenter);}
}
void winMain::fAutoAcce() {if (gAcce<800) gAcce+=1;fAutoAcceShow();}
void winMain::fAutoDece() {if (gAcce>-50) gAcce-=1;fAutoAcceShow();}
void winMain::fJumpBase(int iJ) {gJumpBase=iJ*100;}
void winMain::fAutoJump() {if (gPlay) gJump=gJumpBase;}
void winMain::fAutoBack() {if (gPlay) gJump=-1*gJumpBase;}
/*
    ════════════════════════════════════════════════════════════════════════════════
    Code analysis/programming:  Georges Piedboeuf-Boen  georges.pi.bo@gmail.com
    Functional analysis:        Laurent Tenzer          lt@nova-cinema.org
    Project origin:             Cinéma Nova             http://www.nova-cinema.org
    Made in Brussels            Belgium                 http://www.brussels.be
    ════════════════════════════════════════════════════════════════════════════════
*/