<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Security extends CI_Controller {

	public function __construct(){
		parent::__construct();
		$this->load->model('security_m','securitym');
	}
	public function login(){
		$user = $this->input->post('user',true);
		$password = $this->input->post('password',true);
		if($this->securitym->login($user,$password)){
			$this->load->view('home');
		}else{
			$this->load->view('start');
		}
	}
}

/* End of file security.php */
/* Location: ./application/controllers/security.php */
