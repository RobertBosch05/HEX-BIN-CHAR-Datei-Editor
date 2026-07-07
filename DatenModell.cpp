#include "DatenModell.hpp"

void DatenModell::setData(const std::vector<unsigned char>& data) {
    m_data = data;
    m_modified = false;
}

unsigned char DatenModell::getByte(std::size_t index) const {
    return m_data.at(index);          // wirft std::out_of_range bei Fehler
}

bool DatenModell::setByte(std::size_t index, unsigned char value) {
    if (index >= m_data.size()) return false;
    m_data[index] = value;
    m_modified = true;
    return true;
}

const std::vector<unsigned char>& DatenModell::getData() const {
    return m_data;
}

std::size_t DatenModell::size()       const { return m_data.size(); }
bool        DatenModell::isEmpty()    const { return m_data.empty(); }
bool        DatenModell::isModified() const { return m_modified; }
void        DatenModell::clearModified() { m_modified = false; }
