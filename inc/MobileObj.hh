#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   8


class MobileObj{
    /*!
   * \brief Identyfikuje aktualny stan obiektu.
   *
   * Identyfikuje aktualny stan obiektu. Indeks ten pozwala
   * na wybór z tablicy \link GeomObject::_Cmd4StatDesc _Cmd4StatDesc\endlink
   * odpowiedniego polecenia dla serwera, które reprezentuje aktualne
   * położenie i orientację obiektu.
   */
   int _StateIdx = 0;
  /*!
   * \brief Zestaw sekwencji poleceń symulujących ruch obiektu.
   *
   * Zestaw sekwencji poleceń symulujących ruch obiektu.
   * Każde polecenie odpowiada kolejnym stanom obiektu.
   */
   const char** _Cmd4StatDesc = nullptr;
  
 public:

  /*!
   * \brief Ustawia zestaw poleceń odpowiadających kolejnym stanom
   *        obiektu.
   */
  void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }
  /*!
   * \brief Udostępnia kolejny zestaw poleceń umożliwiających
   *        zespołu obiektu.
   *
   * Udostępnia kolejny zestaw poleceń umożliwiających
   * zespołu obiektu. Ta metoda "udaje" metodę, która w oryginalnym
   * rozwiązaniu powinna wygenerować odpowiednie polecenie na podstawie
   * przechowywanej informacji o położeniu i orientacji obiektu.
   */
  const char* GetStateDesc() const
  {
    return _Cmd4StatDesc[_StateIdx];
  }
  /*!
   * \brief Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *
   *  Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *  Ta metoda "udaje" metodę, która w oryginalnym rozwiązaniu
   *  jest odpowiedzialna za zmianę stanu obiektu, tzn. zmianę jego
   *  położenia lub orientacji.
   */
  bool IncStateIndex() {
    if (_StateIdx >= STATES_NUMBER-1) return false;
    ++_StateIdx;
    return true;
  }
};
#endif