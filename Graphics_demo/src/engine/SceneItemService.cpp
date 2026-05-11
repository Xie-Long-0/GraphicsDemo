#include "SceneItemService.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "entity/xEntity.h"

namespace SceneItemService
{
void removeSelectedItems(QGraphicsScene *scene)
{
    if (scene == nullptr)
        return;

    QGraphicsItem *mayRemoveItem = nullptr;
    auto items = scene->selectedItems();
    for (auto i : items)
    {
        if (items.size() > 1)
        {
            if ((i->type() > xEntity::ET_InterSingle_Start && i->type() < xEntity::ET_InterSingle_End) ||
                (i->type() > xEntity::ET_InterCouple_Start && i->type() < xEntity::ET_InterCouple_End))
            {
                scene->removeItem(i);
                delete i;
                return;
            }

            if (i->parentItem() != nullptr)
                continue;
            if (!i->childItems().isEmpty())
                mayRemoveItem = i;
        }
        else
        {
            scene->removeItem(i);
            delete i;
            return;
        }
    }

    if (mayRemoveItem)
    {
        scene->removeItem(mayRemoveItem);
        delete mayRemoveItem;
    }
}

void removeAllItems(QGraphicsScene *scene)
{
    if (scene == nullptr)
        return;

    while (scene->items().size() > 1)
    {
        auto items = scene->items();
        for (auto i : items)
        {
            if (i->type() == QGraphicsPixmapItem::Type)
                continue;

            scene->removeItem(i);
            if (i->parentItem() != nullptr || i->childItems().isEmpty() != true)
            {
                delete i;
                break;
            }
            else
            {
                delete i;
            }
        }
    }
}
} // namespace SceneItemService
