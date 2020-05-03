////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Logged operations for a map.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>

////////////////////////////////////////////////////////////////////////////////
/// @brief Map that logs operations.
/// @tparam K Key Type
/// @tparam V Value Type
/// @tparam M Map type
////////////////////////////////////////////////////////////////////////////////
template<typename K, typename V, template<typename, typename, typename...> typename M>
class logged_map {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Construct from log filename.
    /// @param _filename Log filename.
    explicit logged_map(std::string _filename) : m_log(_filename) {}

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Forwarding reference version of insertion.
    /// @tparam K_ Key Type
    /// @tparam V_ Value Type
    /// @param _k Key
    /// @param _v Value
    template<typename K_, typename V_>
    void insert(K_&& _k, V_&& _v) {
      m_log << "Insert." << std::endl;
      m_map.emplace(std::forward<K_>(_k), std::forward<V_>(_v));
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Access element.
    /// @param _k Key
    /// @return Value
    V& get(const K& _k) {
      m_log << "Lookup." << std::endl;
      return m_map[_k];
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Remove element.
    /// @param _k Key
    void remove(const K& _k) {
      m_log << "Remove." << std::endl;
      m_map.erase(_k);
    }

  private:
    M<K, V> m_map;       ///< Map
    std::ofstream m_log; ///< Log file
};