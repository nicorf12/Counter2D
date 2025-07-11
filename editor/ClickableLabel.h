// ClickableLabel.h
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>
#include <QApplication>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr)
        : QLabel(parent), seleccionado(false), dragFila(-1), dragColumna(-1), isDraggable(false) {}

    void setSeleccionado(bool sel) {
        seleccionado = sel;
        actualizarEstilo();
    }

    bool estaSeleccionado() const {
        return seleccionado;
    }

    void setDragData(const QPixmap& pixmap, int fila, int columna) {
        dragPixmap = pixmap;
        dragFila = fila;
        dragColumna = columna;
        isDraggable = true;
    }

    void setDraggable(bool draggable) {
        isDraggable = draggable;
    }

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            dragStartPosition = event->pos();
        }
        emit clicked();
        QLabel::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (!(event->buttons() & Qt::LeftButton) || !isDraggable)
            return;

        if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
            return;

        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData;

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << dragFila << dragColumna;
        mimeData->setData("application/x-tile-coords", itemData);

        drag->setMimeData(mimeData);
        drag->setPixmap(dragPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        drag->setHotSpot(QPoint(16, 16)); // Centro del tile

        Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
        Q_UNUSED(dropAction);
    }

private:
    bool seleccionado;
    
    QPoint dragStartPosition;
    QPixmap dragPixmap;
    int dragFila;
    int dragColumna;
    bool isDraggable;

    void actualizarEstilo() {
        if (seleccionado) {
            this->setStyleSheet("border: 2px solid yellow;");
        } else {
            this->setStyleSheet("border: none;");
        }
    }
};

#endif // CLICKABLELABEL_H