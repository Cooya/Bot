package {
    
    import flash.display.*;
    import flash.net.URLRequest;
    import flash.events.*;
    import flash.filesystem.*;
    import flash.system.LoaderContext;
    import flash.system.ApplicationDomain;
    import com.hurlant.crypto.symmetric.PKCS5;
    import by.blooddy.crypto.Base64;
    import com.hurlant.crypto.Crypto;
    import com.ankamagames.dofus.logic.connection.managers.AuthentificationManager;
    import com.ankamagames.dofus.kernel.net.ConnectionsHandler;
    import com.ankamagames.dofus.network.messages.game.chat.ChatClientPrivateMessage;
    import com.ankamagames.jerakine.network.MultiConnection;
    
    public class Dofus extends Sprite {
        
        public function Dofus() {
            
            var a:PKCS5 = new PKCS5();
            var b:Base64 = new Base64();
            var c:Crypto = new Crypto();
            var d:AuthentificationManager = new AuthentificationManager();
            var e:ConnectionsHandler = new ConnectionsHandler();
            var f:ChatClientPrivateMessage = new ChatClientPrivateMessage();

            var loader:Loader = new Loader();
            var url:URLRequest = new URLRequest("/Users/Hugo/Desktop/AnonymBot/trunk/debug/AnonymBot.app/Contents/Resources/RDM/Assets/Raw.swf");
            var lc:LoaderContext = new LoaderContext(false, ApplicationDomain.currentDomain, null);
            loader.load(url, lc);
            loader.contentLoaderInfo.addEventListener(Event.COMPLETE, finish);
        }

        public function finish(e:Event): void {

            var file:File = new File();
            var stream:FileStream = new FileStream();
            stream.open(file, FileMode.WRITE);
            stream.writeUTFBytes(MultiConnection.rep);
            stream.close();
        }
    }
}