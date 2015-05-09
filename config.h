#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

extern QMap<int, QString> mKeySong;

class MyFile {
public:
    MyFile() {}

    static void process_line(const QString &line) {
        int idx = line.split(" ").at(0).toInt();
        QString val = line.split("\"").at(1);
        mKeySong[idx] = val;
    }

    void readFromFile() {
        QFile file("/home/jenny/480/qt/midiUI/defaultConfig.txt");
        if (!file.open(QFile::ReadOnly)) { 
            QMessageBox::information(0, "error", file.errorString());
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            process_line(line);
            line = in.readLine();
        }
        file.close();
    }

    void writeToFile() {
        QFile file("/home/jenny/480/qt/midiUI/defaultConfig.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        int key;
        foreach (key, mKeySong.keys()) 
            out << key << " \"" << mKeySong[key] << "\"" << "\n";
        file.close(); 
    }
    
    virtual ~MyFile(){}
};

