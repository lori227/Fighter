local CBatchUpdateProxy = class("CCheckVersionProxy", CProxy)

function CBatchUpdateProxy.ctor(self, name)
    CProxy.ctor(self, name)
end

return CBatchUpdateProxy