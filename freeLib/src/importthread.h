#ifndef IMPORTTHREAD_H
#define IMPORTTHREAD_H

#include <QSqlDatabase>

#include "library.h"

//способы обновления
#define UT_FULL 10
#define UT_DEL_AND_NEW 11
#define UT_NEW 12


class ImportThread : public QObject
{
    Q_OBJECT
public:
    explicit ImportThread(QObject *parent = 0);
    void start(uint id_, const SLib &lib, uchar update_type, bool save_only);
    //void SaveLibrary();
    bool loop;
signals:
    void Message(QString str);
    void End();
public slots:
    void process();
    void break_import();
protected:
    void importFB2(const QString &path,int &count);
    void importFB2_main(const QString &path);

    void readFB2(const QByteArray &ba, QString file_name, QString arh_name,qint32 file_size=0);
    void readEPUB(const QByteArray &ba, QString file_name, QString arh_name,qint32 file_size=0);
    void readFB2_test(const QByteArray& ba, QString file_name, QString arh_name);
private:
    QString sInpxFile_;
    QString sName_;
    QString sPath_;
    bool _save_only;
    uchar nUpdateType_;
    bool bFirstAuthorOnly;
    bool bWoDeleted_;
    uint  idLib_;
    QList<uint> listIdBookInLib_;
    QSqlQuery *query;
    qlonglong AddSeria(const QString &str, qlonglong libID, int tag);
    qlonglong addAuthor(const SAuthor &author, uint libID, uint idBook, bool first_author, int tag);
    uint AddBook(qlonglong star, const QString &name, qlonglong id_seria, int num_in_seria, const QString &file,
                 int size, int IDinLib, bool deleted, const QString &format, QDate date, const QString &language, const QString &keys, qlonglong id_lib, const QString &archive, int tag);

    qlonglong AddGenre(qlonglong idBook, QString sGenre, qlonglong id_lib);

};

#endif // IMPORTTHREAD_H
