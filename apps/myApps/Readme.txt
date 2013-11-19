ダウンロードありがとうございます。
Footplinkは遠隔地の人の動きを足跡として投影するアプリケーションです。

配付するアプリケーションは以下の3つとなります。
①FootplinkClient.exe
	出力側アプリケーション本体です。
	キーコマンド
		1 現在のデータから
		2 記録したデータを最初から
		c 今迄のデータをクリア
		5 ボールを表示
		6 ボールを非表示

②FootplinkCkientSettingApp.exe
	①の入力元となるCSVファイルの場所を変更する際に用います。
	別途記録データとして保存したデータを閲覧する際にはまずこちらでCSVファイルを指定してください。

③runserver.bat
	遠隔地の入力を受け取りCSVファイルとして出力するサーバー(manage.py)を起動します。

④data.csv
	③の出力先となる、最新データファイルです。①はこれを入力として足跡を出力します。
	これをリネームして別ファイルとして保存しておけば、過去のデータを保存しておくことができます。
	過去のデータを閲覧する場合は①の起動前に②で入力パスの変更を行ってください。

＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

FootplinkClient起動方法

[1]簡単起動
1.runserver.batをダブルクリック
2.入力先PCでKinectClient.exeを起動
3.FootplinkCkientSettingApp.exeを起動し、カレントディレクトリ上のdata.csvを指定
4.FootplinkClient.exeをダブルクリック

[2]データを別ファイルとして保存
1.data.csvをリネーム

[3]別ファイルとして保存したcsvファイルを閲覧
1.runserver.batをダブルクリック
2.入力先PCでKinectClient.exeを起動
3.FootplinkCkientSettingApp.exeを起動し、csvファイルのパスを指定
4.FootplinkClient.exeをダブルクリック
