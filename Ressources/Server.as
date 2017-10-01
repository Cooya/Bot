package {
	import flash.net.Socket;
	import flash.net.ServerSocket;
	import flash.events.ServerSocketConnectEvent;
	import flash.events.ProgressEvent;
	import flash.utils.ByteArray;
	
	public class Server {
	
		private var server:ServerSocket;
		private var client:Socket;
	
		public function Server(port:int, IP:String) : void {
			server = new ServerSocket();
			server.bind(port, IP);
			if (server.bound){
				server.addEventListener(ServerSocketConnectEvent.CONNECT, onConnect);
				server.listen();
			}
		}
		
		private function onConnect(event:ServerSocketConnectEvent) : void {
            client = event.socket;
            client.addEventListener(ProgressEvent.SOCKET_DATA, onClientSocketData);
        }
		
		private function onClientSocketData(event:ProgressEvent) : void {
            var buffer:ByteArray = new ByteArray();
            client.readBytes(buffer, 0, client.bytesAvailable);

			answer(buffer);
        }
		
		private function answer(buffer:ByteArray) : void {
			client.writeBytes(buffer);
			client.flush();
			client.close();
		}
	
	}