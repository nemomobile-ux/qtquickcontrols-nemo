#include "ringindicator.h"

#include <QTimer>

RingIndicator::RingIndicator(QQuickItem *parent)
    : QQuickItem(parent)
    , m_startAngle(0)
    , m_stopAngle(90)
    , m_lineHeight(1)
    , m_color(Qt::white)
{
    setFlag(ItemHasContents, true);
    setAntialiasing(true);
}

QSGNode *RingIndicator::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;
    int anglOfindication = (int)normalizeAngile(m_stopAngle-m_startAngle);
    int radius = qMin(width(),height())/2;
    bool isBack = false;
    if(m_stopAngle < m_startAngle) {
        isBack = true;
    }

    if (!oldNode) {
        node = new QSGGeometryNode();
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), anglOfindication+1);
        QSGFlatColorMaterial* material = new QSGFlatColorMaterial();

        geometry->setDrawingMode(QSGGeometry::DrawPoints);
        material->setColor(m_color);

        node->setGeometry(geometry);
        node->setMaterial(material);

        node->setFlags(QSGNode::OwnsGeometry|QSGNode::OwnsMaterial);

    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(anglOfindication+1, 0);
    }

    geometry->setLineWidth(m_lineHeight);

    // verify material
    QSGMaterial *material = node->material();
    QSGFlatColorMaterial *flatMaterial = static_cast<QSGFlatColorMaterial*>(material);

    if(flatMaterial->color() != m_color) {
        flatMaterial->setColor(m_color);
        node->markDirty(QSGNode::DirtyMaterial);
    }

    //geometry->vertexDataAsPoint2D()[0].set(radius, radius);
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    node->markDirty(QSGNode::DirtyGeometry);

    for (int i = 0; i < anglOfindication+1; ++i) {
        int ang;
        if(isBack) {
            ang = i+m_stopAngle;
        } else {
            ang = i+m_startAngle;
        }
        double rad = qDegreesToRadians(double(ang - 90));
        float x = std::cos(rad)*radius+width()/2;
        float y = std::sin(rad)*radius+width()/2;
        vertices[i].set(x,y);

        /*float x1 = qCos(rad)*(radius-m_lineHeight)+width()/2;
        float y1 = qSin(rad)*(radius-m_lineHeight)+width()/2;
        vertices[i*2+1].set(x1,y1);*/
    }

    return node;
}

void RingIndicator::setStartAngle(float startAngle)
{
    startAngle = normalizeAngile(startAngle);

    if(startAngle != m_startAngle) {
        m_startAngle = startAngle;
        emit startAngleChanged();
        update();
    }
}

void RingIndicator::setStopAngle(float stopAngle)
{
    stopAngle = normalizeAngile(stopAngle);

    if(stopAngle != m_stopAngle) {
        m_stopAngle = stopAngle;
        emit stopAngleChanged();
        update();
    }
}

void RingIndicator::setLineHeight(float lineHeight)
{
    if(lineHeight >+ 0 && lineHeight != m_lineHeight) {
        m_lineHeight = lineHeight;
        emit lineHeightChanged();
        update();
    }
}

void RingIndicator::setColor(QString color)
{
    QColor newColor(color);
    if(newColor != m_color) {
        m_color = newColor;
        emit colorChanged();
        update();
    }
}

float RingIndicator::normalizeAngile(float ang)
{
    if(ang > 360) {
        int circles = (int)(ang/360);
        ang = ang-360*circles;
    }

    if(ang < 0) {
        int circles = (int)(ang/360);
        ang = ang+360*circles;
    }

    return abs(ang);
}
