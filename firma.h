#ifndef FIRMA_H
#define FIRMA_H

#include <QString>

class Firma
{
public:
    explicit Firma(QString n, QString b, QString em, QString adr, QString kodp, QString mias, QString woje, QString kraj, QString nip);
    //akcesory składowych prywatnych klasy
    QString getNazwa() const;
    QString getBranza() const;
    QString getEmail() const;
    QString getAdres() const;
    QString getKodPocztowy() const;
    QString getMiasto() const;
    QString getWojewodztwo() const;
    QString getKraj() const;
    QString getNip() const;

    void setNazwa(QString nazwa);
    void setBranza(QString branza);
    void setEmail(QString email);
    void setAdres(QString adres);
    void setKodPocztowy(QString kodPocztowy);
    void setMiasto(QString miasto);
    void setWojewodztwo(QString wojewodztwo);
    void setKraj(QString kraj);
    void setNip(QString nip);

    //metody zarządzające stanem danych
    void modyfikuj();

private:
    QString nazwa;
    QString branza;
    QString email;
    QString adres;
    QString kodPocztowy;
    QString miasto;
    QString wojewodztwo;
    QString kraj;
    QString nip;
};

#endif // FIRMA_H
