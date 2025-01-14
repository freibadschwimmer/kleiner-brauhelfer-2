#include "tabzusammenfassung.h"
#include "ui_tabzusammenfassung.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QDesktopServices>
#include "brauhelfer.h"
#include "settings.h"
#include "templatetags.h"

extern Brauhelfer* bh;
extern Settings* gSettings;

TabZusammenfassung::TabZusammenfassung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabZusammenfassung)
{
    ui->setupUi(this);

    connect(bh, SIGNAL(modified()), this, SLOT(updateAll()));
    connect(bh, SIGNAL(discarded()), this, SLOT(updateAll()));
    connect(bh->sud(), SIGNAL(loadedChanged()), this, SLOT(updateAll()));
}

TabZusammenfassung::~TabZusammenfassung()
{
    delete ui;
}

void TabZusammenfassung::saveSettings()
{
}

void TabZusammenfassung::restoreView()
{
}

void TabZusammenfassung::updateAll()
{
    if (bh->sud()->getStatus() == Sud_Status_Rezept)
        ui->webview->setHtmlFile("spickzettel.html");
    else
        ui->webview->setHtmlFile("zusammenfassung.html");
    TemplateTags::render(ui->webview, TemplateTags::TagAll, bh->sud()->row());
}

void TabZusammenfassung::on_btnToPdf_clicked()
{
    gSettings->beginGroup("General");

    QString path = gSettings->value("exportPath", QDir::homePath()).toString();

    QString fileName = bh->sud()->getSudname();
    QString filePath = QFileDialog::getSaveFileName(this, tr("PDF speichern unter"),
                                     path + "/" + fileName +  ".pdf", "PDF (*.pdf)");
    if (!filePath.isEmpty())
    {
        gSettings->setValue("exportPath", QFileInfo(filePath).absolutePath());
        ui->webview->printToPdf(filePath);
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }

    gSettings->endGroup();
}
