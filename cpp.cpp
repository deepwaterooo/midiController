class someClass : public QObject {  
    Q_OBJECT  
signals: //信号定义区  
    friend class ClassTemplate; // 此处定义不合语法
};
