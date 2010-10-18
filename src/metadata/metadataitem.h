/*
  Copyright (c) 2004-2010 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  $Id$

*/

//-----------------------------------------------------------------------------
#ifndef FR_METADATAITEM_H
#define FR_METADATAITEM_H

#include <wx/string.h>

#include <algorithm>
#include <vector>

#include "core/ObjectWithHandle.h"
#include "core/ProcessableObject.h"
#include "core/Subject.h"
#include "metadata/MetadataClasses.h"
#include "sql/Identifier.h"

class Dependency;
class MetadataItemVisitor;
//-----------------------------------------------------------------------------
typedef enum { ntUnknown, ntRoot, ntServer, ntDatabase,
    // each item type and (if applicable) its parent type
    ntTable, ntTables, ntView, ntViews, ntProcedure, ntProcedures,
    ntTrigger, ntTriggers, ntGenerator, ntGenerators, ntFunction, ntFunctions,
    ntSysTable, ntSysTables, ntException, ntExceptions, ntDomain, ntDomains,
    ntRole, ntRoles, ntColumn, ntParameter, ntIndex,
    ntLastType
} NodeType;
//-----------------------------------------------------------------------------
NodeType getTypeByName(wxString name);
wxString getNameOfType(NodeType type);
//-----------------------------------------------------------------------------
class MetadataItem: public Subject, public ObjectWithHandle<MetadataItem>,
    public ProcessableObject
{
private:
    MetadataItem* parentM;
    NodeType typeM;

    enum LoadState { lsNotLoaded, lsLoadPending, lsLoaded, lsNotAvailable };
    LoadState childrenLoadedM;
    LoadState descriptionLoadedM;
    LoadState propertiesLoadedM;

    wxString descriptionM;
    void ensureDescriptionLoaded();

protected:
    Identifier identifierM;

    template <class T>
    T* getParentObjectByType() const
    {
        MetadataItem *m = getParent();
        while (m)
        {
            T* t = dynamic_cast<T*>(m);
            if (t)
                return t;
            m = m->getParent();
        }
        return 0;
    }

    MetadataItem* getParentObjectOfType(NodeType type) const;

    virtual void loadDescription();
    virtual void saveDescription(wxString description);
    void saveDescription(wxString saveStatement, wxString description);

    virtual void loadProperties();
    void setPropertiesLoaded(bool loaded);

    virtual void doSetChildrenLoaded(bool loaded);
    virtual void loadChildren();
    virtual void lockChildren();
    virtual void unlockChildren();

    void resetPendingLoadData();

public:
    MetadataItem();
    MetadataItem(NodeType type);
    virtual ~MetadataItem();

    virtual void lockSubject();
    virtual void unlockSubject();

    void getDependencies(std::vector<Dependency>& list, bool ofObject);  // load from db
    void getDependencies(std::vector<Dependency>& list, bool ofObject,
        const wxString& field);  // load from db

    // will return 0 if no database is assigned
    Database* findDatabase() const;
    // will throw FRError if no database is assigned
    Database* getDatabase(const wxString& callingMethod) const;

    virtual void invalidate();

    // items description (in database)
    wxString getDescription();
    bool getDescription(wxString& description);
    void invalidateDescription();
    void setDescription(wxString description);

    bool childrenLoaded() const;
    void ensureChildrenLoaded();
    void ensurePropertiesLoaded();
    void loadPendingData();
    bool propertiesLoaded() const;
    void setChildrenLoaded(bool loaded);

    virtual bool getChildren(std::vector<MetadataItem *>& temp);
    virtual size_t getChildrenCount() const { return 0; };
    void drop();    // removes its children (by calling drop() for each) and notifies it's parent

    // returns complete DROP SQL statement
    virtual wxString getDropSqlStatement() const;

    // getters/setters
    virtual MetadataItem *getParent() const;
    void setParent(MetadataItem *parent);
    virtual wxString getName_() const;
    virtual wxString getQuotedName() const;
    virtual Identifier getIdentifier() const;
    virtual void setName_(wxString name);
    virtual NodeType getType() const;
    void setType(NodeType type);
    void setProperties(MetadataItem* parent, const wxString& name, NodeType type);

    // returns the name of the data type (f. ex. TABLE)
    virtual const wxString getTypeName() const;

    // returns the item path, currently only used to store settings in config().
    // It could also be used to locate items in the DBH tree.
    virtual const wxString getItemPath() const;

    // returns the id wxString of the metadata item that contributes to the path. The
    // predefined implementation just returns getId().
    virtual const wxString getPathId() const;
    // returns the id of the item (to be saved in config files, etc.).
    // The predefined implementation just returns getName().
    virtual const wxString getId() const;

    // returns true if the metadata item is a system (as opposed to user-defined) item.
    virtual bool isSystem() const;

    virtual void acceptVisitor(MetadataItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
//! masks the object it points to so others see it transparently
class Dependency: public MetadataItem
{
private:
    MetadataItem *objectM;
    std::vector<wxString> fieldsM;

public:
    virtual MetadataItem *getParent() const;
    virtual wxString getName_() const;
    virtual NodeType getType() const;
    virtual const wxString getTypeName() const;
    MetadataItem *getDependentObject() const;

    Dependency(MetadataItem *object);
    wxString getFields() const;
    void getFields(std::vector<wxString>& fields) const;
    void addField(const wxString& name);
    void setFields(const std::vector<wxString>& fields);
    bool hasField(const wxString& name) const;
    bool operator== (const Dependency& other) const;
    bool operator!= (const Dependency& other) const;
    virtual void acceptVisitor(MetadataItemVisitor* visitor);
};
//-----------------------------------------------------------------------------
#endif //FR_METADATAITEM_H
