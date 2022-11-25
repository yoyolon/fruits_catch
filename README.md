# Fruits Catch Game

## 概要

[Game Programming in C++](https://github.com/gameprogcpp/code)のプログラムをベースに作成したゲームです．空から落下してくるフルーツをプレイヤーを移動させてキャッチします．アセットはAdobe Photoshopで自作しました．

<div align="center">
    <img src="assets/title.png">
</div>

## 開発環境

- Windows 10  
- Microsoft Visual Studio 2019  
- C++17  

## 外部ライブラリ

- [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2)
- [SDL_image](https://github.com/libsdl-org/SDL_image/)

## 実行方法

SDLライブラリをインストールして，Visual Stusioのプロパティをパスが通るように変更してビルドしてください．環境構築の流れは[こちらの記事](https://www.kuroshum.com/entry/2019/07/18/%E3%82%B2%E3%83%BC%E3%83%A0%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0C++%E3%81%AE%E7%92%B0%E5%A2%83%E6%A7%8B%E7%AF%89(SDL))の記事が参考になると思います．

## 遊び方

制限時間30秒の間，空からフルーツが落ちてくるので十字キーでプレイヤーを操作してキャッチします．フルーツをキャッチするとスコアが加算されます．赤いフルーツは20点，青いフルーツは50点，ピンクのフルーツは200点です．
<div>
    <img src="assets/apple.png">
    <img src="assets/bery.png">
    <img src="assets/peach.png">
</div>

時々，上記のフルーツ以外が落ちてくることがあります．
ピンクのオブジェクトはキャッチするとスコアが100点減算されてしまいます．時計のオブジェクトはキャッチすると制限時間が5秒延長します．

<div>
    <img src="assets/dragon.png">
    <img src="assets/watch.png">
</div>



## 参考文献

Sanjay Madhav(著), 吉川邦夫(翻訳), 今給黎 隆(監訳) "ゲームプログラミング C++" 2018.  
Sanjay Madhav "[Game Programming in C++ Code](https://github.com/gameprogcpp/code)" 2017.  