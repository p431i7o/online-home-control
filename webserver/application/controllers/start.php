<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Start extends CI_Controller {

	public function __construct(){
		parent::__construct();
		$this->load->model('security_m','securitym');
	}	
	public function index(){
		if($this->securitym->logged()){
			$this->load->view('home');
		}else{
			$this->load->view('welcome_message')
		};
	}
}

/* End of file welcome.php */
/* Location: ./application/controllers/welcome.php */
