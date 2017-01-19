三個執行檔
ai_client ai_stdio play_game

只有ai_client會用於比賽，屬於線上測試平台
ai_stdio是助教給的簡單測試，可以直接忽略
play_game是我自己用來training的平台

先前是使用某位同學架設的2584.nctu.me這個平台做線上測試，
對應的IP是140.113.194.120
但是我現在把平台指向助教開的平台，應該就是明天比賽用的平台
對應的IP是140.113.167.52
就我所知，某同學的平台比較嚴格XDDD

另外，這版的ai_client可以自動偵測是否為同一局，
因此不需要像之前每次跑完一局後要被kill(control C)掉
